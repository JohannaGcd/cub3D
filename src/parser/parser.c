/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:21:58 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/13 16:24:19 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

static void init_cub3d_data(t_cub3d *data)
{
    data->textures.path[NO] = NULL;
    data->textures.path[SO] = NULL;
    data->textures.path[WE] = NULL;
    data->textures.path[EA] = NULL;
    data->floor.r = -1;
    data->floor.g = -1;
    data->floor.b = -1;
    data->ceiling.r = -1;
    data->ceiling.g = -1;
    data->ceiling.b = -1;
    data->map.grid = NULL;
    data->map.width = 0;
    data->map.height = 0;
    data->map.player_x = -1;
    data->map.player_y = -1;
    data->map.player_dir = '\0';
    data->metadata_flags = 0;
}
static bool has_cub_extension(const char *filename)
{
    size_t  len;

    len = ft_strlen(filename);
    if (len < 4)
        return (false);
    return (ft_strncmp(&filename[len - 4], ".cub", 4) == 0);
}

/*
* Reads file line-by-line and processes metadata (textures, colors) and map.
* Implements the parsing in two steps:
* Phase 1: Metadata parsing
* - skips empty lines
* - parses texture and color lines
* - tracks completion with bit flags
* - transitions to map when ALL_METADATA flag is set and a map line is detected
* Phase 2: Map parsing
* - detects map start (first line with valid map chars after ALL_METADATA is set)
* - dynamically grows map array as lines are read
* - skips empty lines in map section
* - calculates dimensions and finds player position after all lines have been read
*/
static int  read_file_line_by_line(int fd, t_cub3d *data)
{
    char    *line;
    int     line_num;
    bool    map_started;

    line_num = 1;
    map_started = false;
    line = get_next_line(fd);
    while (line)
    {
        if (!map_started)
        {
            if (is_empty_line(line))
            {
                free(line);
                line = get_next_line(fd);
                line_num++;
                continue;
            }
            if (parse_metadata_line(line, data, line_num) == -1)
            {
                free(line);
                return (-1);
            }
            printf("BACK read_file_line_ny_line BEFORE CHECKING FLAG");
            if (is_metadata_complete(data) && is_map_line(line))
            {
                map_started = true;
                build_map(&data->map, line);
                free(line);
                line = get_next_line(fd);
                line_num++;
                continue;
            }
        }
        else
        {
            if (is_map_line(line) || is_empty_line(line))
            {
                if (!is_empty_line(line))
                    build_map(&data->map, line);
            }
            else
            {
                free(line);
                printf("Error\nIvalid character in map\n");
                return (-1);
            }
        }
        free(line);
        line = get_next_line(fd);
        line_num++;
    }
    if (!is_metadata_complete(data))
    {
        printf("Error\nMetadata is incomplete.\n");
        return (-1);
    }
    if (!map_started || data->map.height == 0)
    {
        printf("Error\nMap not found or empty.\n");
        return (-1);
    }
    calculate_map_dimensions(&data->map);
    return (find_player_position(data));
}

/*
* Main parser function - entry point for parsing .cub files.
* Orchestrates the 4 steps of the parsing process:
* 1. File reading (opens file, uses get_next_line)
* 2. Metadata parsing (parses textures and colors with bit flags)
* 3. Map parsing (dynamically grows map array)
* 4. Map validation (validates final map using flood fille)

* Returns:
* 0 on success
* -1 on error (with error messages printed)
* On error, frees all allocated memory before returning.
*/

int parse_cub_file(char *filename, t_cub3d *data)
{
    int fd;

    if (!filename || !data)
    {
        printf("Error\nInvalid arguments\n");
        return (-1);
    }
    if (!has_cub_extension(filename))
    {
        printf("Error\nFile must have .cub extension\n");
        return (-1);
    }
    init_cub3d_data(data),
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nCannot open file\n");
        return (-1);
    }
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

// TO_DO:
// 3. GET RECTANGULAR MAP 
// 4. PUSH TO GITHUB
// 5. NORMINETTE
// 6. REPLACE PRINTF:
//      IF IT'S OUR FUNCTION, USE FT_ERROR, OTHERWISE (LIKE OPEN) USE PERROR