/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_misc_utils2.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/21 13:50:49 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/21 14:41:49 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	init_cub3d_data(t_cub3d *data)
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

int	is_directory(char *filename)
{
	int	fd;

	fd = open(filename, O_DIRECTORY);
	if (fd >= 0)
	{
		close(fd);
		return (1);
	}
	return (0);
}

bool	has_cub_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (false);
	return (ft_strncmp(&filename[len - 4], ".cub", 4) == 0);
}

int	interpret_res(int result, int *map_started)
{
	if (result == 1)
	{
		*map_started = 1;
		return (0);
	}
	if (result == -1)
		return (-1);
	return (0);
}

bool	is_metadata_complete(t_cub3d *data)
{
	return (data->metadata_flags == ALL_METADATA);
}