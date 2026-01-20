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

void	print_level_val(t_level *l)
{
	printf("x: %i, y: %i\n", l->x_row, l->y_col);
	printf("player dir: %f\n", l->player_dir_deg);
	printf("playerPos (%f, %f)\n", l->player_pos_x, l->player_pos_y);
	int	i;
	int	j;

	j = -1;
	while (l->map[++j])
	{
		i = -1;
		while (l->map[j][++i])
			printf("%c", l->map[j][i]);
		printf("\n");
	}
} 

int	main(int argc, char **argv)
{
	t_mlx	mlx_data;
	t_cub3d	cub3d;

	if (argc != 2)
	{
		printf("Error\nUse: ./cub3d <map_file.cub>\n");
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
	convert_map_to_level(&cub3d);
	print_level_val(&cub3d.level);
	hook_events(&mlx_data, &cub3d);

	mlx_loop_hook(mlx_data.instance, game_loop, &cub3d);
	mlx_loop(mlx_data.instance);
	clean_up(&mlx_data, &cub3d);
	return (0);
}
