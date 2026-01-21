/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_err.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/21 14:24:49 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/21 14:43:10 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_error(char *error_str)
{
	size_t	str_len;

	str_len = ft_strlen(error_str);
	write(STDERR_FILENO, error_str, str_len);
	write(STDERR_FILENO, "\n", 1);
	return (-1);
}

int	ft_error_detail(char *error_str, char *detail)
{
	ft_error(error_str);
	ft_error(detail);
	return (-1);
}

void	free_dbl_ptr(int **arr, int count)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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