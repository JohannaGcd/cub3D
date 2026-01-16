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

void	convert_map_to_level(t_cub3d *cub3d)
{
	t_level	*l;
	t_map	*m;

	l = &cub3d->level;
	m = &cub3d->map;
	l->map = m->grid;
	l->y_col = m->width;
	l->x_row = m->height;
	l->player_pos_x = m->player_x;
	l->player_pos_y = m->player_y;
	if (m->player_dir == 'N')
		l->player_dir_deg = 90.0;
	if (m->player_dir == 'E')
		l->player_dir_deg = 0.0;
	if (m->player_dir == 'S')
		l->player_dir_deg = 270.0;
	if (m->player_dir == 'W')
		l->player_dir_deg = 180.0;
}

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
		return (-1);
	convert_map_to_level(&cub3d);
	print_level_val(&cub3d.level);
	hook_events(&mlx_data, &cub3d);

	mlx_loop_hook(mlx_data.instance, game_loop, &cub3d);
	mlx_loop(mlx_data.instance);
	//clean_up();
	return (0);
}
