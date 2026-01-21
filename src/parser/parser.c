/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:21:58 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/21 15:53:54 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * Implements step 1 of read_file_line_by_line: Metadata Parsing
 * - skips empty lines
 * - parses texture and color lines, tracking completion with bit flags
 * - transitions to map when ALL_METADATA flag is set and a map line is detected
 */
static int	handle_metadata_line(t_cub3d *data, char *line)
{
	if (is_empty_line(line))
		return (0);
	if (is_metadata_complete(data) && is_map_line(line))
	{
		build_map(&data->map, line);
		return (1);
	}
	if (parse_metadata_line(line, data) == -1)
		return (-1);
	return (0);
}

/* Implements step 2 of read_file_line_by_line: Map Parsing
 * - skips empty lines and detects map start
 * - dynamically grows map array as lines are read
 * - skips empty lines in map section
 */
static int	handle_map_line(t_cub3d *data, char *line)
{
	if (is_empty_line(line))
		return (0);
	if (is_map_line(line))
	{
		build_map(&data->map, line);
		return (0);
	}
	return (ft_error("Invalid char in map"));
}

static int	check_for_parsing_err(t_cub3d *data, int map_started)
{
	if (!is_metadata_complete(data))
		return (ft_error("Metadata is incomplete"));
	if (!map_started || data->map.height == 0)
		return (ft_error("Map not found or empty"));
	return (0);
}

/*
 * Reads file line-by-line and processes metadata (textures, colors) and map.
 * Implements the parsing in two steps:
 * Phase 1: Metadata parsing
 * Phase 2: Map parsing
 * Finally, calculates dimensions and finds player position
 */
static int	read_file_line_by_line(int fd, t_cub3d *data)
{
	char	*line;
	int		line_num;
	int		map_started;
	int		res;

	line_num = 1;
	map_started = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_started)
			res = handle_metadata_line(data, line);
		else
			res = handle_map_line(data, line);
		free(line);
		if (res != 0 && interpret_res(res, &map_started) == -1)
			return (-1);
		line = get_next_line(fd);
		line_num++;
	}
	if (check_for_parsing_err(data, map_started) == -1)
		return (-1);
	calculate_map_dimensions(&data->map);
	return (find_player_position(data));
}

/*
* Main parser function - entry point for parsing .cub files.
* Orchestrates the 4 steps of the parsing process:
* 1. File reading (opens file, uses get_next_line)
* 2. Metadata parsing (parses textures and colors with bit flags)
* 3. Map parsing (dynamically grows map array)
* 4. Map validation (validates final map using flood fill)

* Returns:
* 0 on success
* -1 on error (with error messages printed)
* On error, frees all allocated memory before returning.
*/
int	parse_cub_file(char *filename, t_cub3d *data)
{
	int	fd;

	if (!filename || !data)
		return (ft_error("Invalid arguments"));
	if (!has_cub_extension(filename))
		return (ft_error("File must have .cub extension"));
	if (is_directory(filename))
		return (ft_error("File is a directory"));
	init_cub3d_data(data);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("Error\nCannot open file\n"), -1);
	if (read_file_line_by_line(fd, data) == -1)
	{
		close(fd);
		free_parser_data(data);
		return (-1);
	}
	close(fd);
	if (validate_map(data) == -1)
	{
		free_parser_data(data);
		return (-1);
	}
	return (0);
}
/* TODO FIX PARSER
- NO EMPTY LINES IN MAP
- NO CHAR IN COLORS */