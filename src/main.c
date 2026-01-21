/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: zivanov <zivanov@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/12/27 13:57:38 by zivanov       #+#    #+#                 */
/*   Updated: 2026/01/13 16:18:57 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(int argc, char **argv)
{
	t_mlx	mlx_data;
	t_cub3d	cub3d;

	if (argc != 2)
	{
		ft_error("Error\nUse: ./cub3d <map_file.cub>\n");
		return (1);
	}
	if (parse_cub_file(argv[1], &cub3d) == -1)
	{
		free_parser_data(&cub3d);
		return (1);
	}
	if (init_data(&mlx_data, &cub3d) != 0)
	{
		clean_up(&mlx_data, &cub3d);
		return (-1);
	}
	hook_events(&mlx_data, &cub3d);
	mlx_loop_hook(mlx_data.instance, game_loop, &cub3d);
	mlx_loop(mlx_data.instance);
	clean_up(&mlx_data, &cub3d);
	return (0);
}
