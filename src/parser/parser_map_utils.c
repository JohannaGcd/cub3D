/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_map_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 13:13:47 by jojo          #+#    #+#                 */
/*   Updated: 2026/01/19 13:42:51 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * Helper function for flood_fill implementation
 * to measure the length of the line.
 */
int	get_line_width(char *line)
{
	int	len;

	if (!line)
		return (0);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	return (len);
}

bool	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == ' ' || c == '\t');
}

void	free_parser_data(t_cub3d *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < 4)
	{
		free(data->textures.path[i]);
		data->textures.path[i] = NULL;
		i++;
	}
	if (data->map.grid)
	{
		i = 0;
		while (data->map.grid[i])
		{
			free(data->map.grid[i]);
			i++;
		}
		free(data->map.grid);
		data->map.grid = NULL;
	}
}

bool	is_empty_line(char *line)
{
	if (!line)
		return (true);
	while (*line)
	{
		if (*line != ' ' && *line != '\t' && *line != '\n')
			return (false);
		line++;
	}
	return (true);
}
