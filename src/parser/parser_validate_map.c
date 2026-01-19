/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_validate_map.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:22:01 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/19 17:40:20 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * Checks each map character, one by one.
 * returns an error if an unauthorized character is met.
 */
int	validate_characters(t_cub3d *data)
{
	int	y;
	int	x;

	y = 0;
	while (data->map.grid[y])
	{
		x = 0;
		while (data->map.grid[y][x] && data->map.grid[y][x] != '\n')
		{
			if (!is_valid_map_char(data->map.grid[y][x]))
			{
				printf("Error\nInvalid character '%c' at position (%d,%d)\n",
					data->map.grid[y][x], y, x);
				return (-1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

/*
 * Tries to open each texture file.
 * Returns -1 upon error.
 */
int	validate_texture_files(t_cub3d *data)
{
	int	fd;

	if (!data->textures.path[NO])
		return (-1);
	fd = open(data->textures.path[NO], O_RDONLY);
	if (fd == -1)
		return (ft_error_detail("Cannot open texture file", data->textures.path[NO]));
	close(fd);
	fd = open(data->textures.path[SO], O_RDONLY);
	if (fd == -1)
		return (ft_error_detail("Cannot open texture file", data->textures.path[SO]));
	close(fd);
	fd = open(data->textures.path[WE], O_RDONLY);
	if (fd == -1)
		return (ft_error_detail("Cannot open texture file", data->textures.path[WE]));
	close(fd);
	fd = open(data->textures.path[EA], O_RDONLY);
	if (fd == -1)
		return (ft_error_detail("Cannot open texture file", data->textures.path[EA]));
	close(fd);
	return (0);
}

/*
 * Recursive function for flood fill:
 * Base case: checks if outside of boundaries (rows, then columns)
 * Marks cell as visited
 * Calls itself with the next index is all directions (y + 1 and y - 1,
	same for x);
 */
static int	flood_fill_recursive(char **map, int **visited, int row, int col,
		int height)
{
	int	line_width;

	if (row < 0 || row >= height || !map[row])
		return (1);
	line_width = get_line_width(map[row]);
	if (col < 0 || col >= line_width)
		return (1);
	if (visited[row][col] || map[row][col] == '1')
		return (0);
	if (map[row][col] == ' ' || map[row][col] == '\n' || map[row][col] == '\0')
		return (1);
	visited[row][col] = 1;
	if (flood_fill_recursive(map, visited, row, col + 1, height))
		return (1);
	if (flood_fill_recursive(map, visited, row, col - 1, height))
		return (1);
	if (flood_fill_recursive(map, visited, row + 1, col, height))
		return (1);
	if (flood_fill_recursive(map, visited, row - 1, col, height))
		return (1);
	return (0);
}

/*
 * Flood fill tutorial: https://www.youtube.com/watch?v=RjO-HDjRMpM
 * Create a visited array to track positions
 * which have already been checked (avoids infinite loop)
 * Start flood fill from player position:
 * If flood fill reaches boundaries, map is not closed (returns an error)
 */
int	flood_fill_validation(t_cub3d *data)
{
	int	**visited;
	int	x;
	int	result;

	visited = malloc(sizeof(int *) * data->map.height);
	if (!visited)
		return (ft_error("Memory allocation failed"));
	x = 0;
	while (x < data->map.height)
	{
		visited[x] = malloc(sizeof(int) * data->map.width);
		if (!visited[x])
		{
			while (x-- > 0)
				free(visited[x]);
			free(visited);
			return (-1);
		}
		ft_intset(visited[x], 0, data->map.width);
		x++;
	}
	result = flood_fill_recursive(data->map.grid, visited, data->map.player_y,
			data->map.player_x, data->map.height);
	x = 0;
	while (x < data->map.height)
		free(visited[x++]);
	free(visited);
	if (result)
		return (ft_error("Map is not properly enclosed by walls"));
	return (0);
}

/*
 * Main validation function, which orchestrates each step:
 * - Validates that there are only authorised map chars
 * - Map should be enclosed (using flood fill)
 * - Texture files should all exist and be readable
 * Returns -1 upon error, 0 on success
 */
int	validate_map(t_cub3d *data)
{
	if (validate_characters(data) == -1)
		return (-1);
	if (flood_fill_validation(data) == -1)
		return (-1);
	if (validate_texture_files(data) == -1)
		return (-1);
	return (0);
}
