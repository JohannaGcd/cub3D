/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_map_utils.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 13:13:47 by jojo          #+#    #+#                 */
/*   Updated: 2026/01/21 14:21:43 by jguacide      ########   odam.nl         */
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

void	calculate_map_dimensions(t_map *map)
{
	int	max_width;
	int	i;
	int	len;

	max_width = 0;
	i = 0;
	while (map->grid[i])
	{
		len = ft_strlen(map->grid[i]);
		if (map->grid[i][len - 1] == '\n')
			len--;
		if (len > max_width)
			max_width = len;
		i++;
	}
	map->width = max_width;
}

/*
 * Detects if a line is a valid map line, ie:
 * Contains valid map characters (0,1,N,S,E,W) or whitespaces
 */
bool	is_map_line(char *line)
{
	int		i;
	bool	has_map_char;

	if (!line)
		return (false);
	i = 0;
	has_map_char = false;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_map_char = true;
		else if (line[i] != ' ' && line[i] != '\t')
			return (false);
		i++;
	}
	return (has_map_char);
}
