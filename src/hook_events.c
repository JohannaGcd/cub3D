/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:19:22 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 13:49:21 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(void *mlx_instance)
{
	mlx_loop_end(mlx_instance);
	return (0);
}

/*
 * I might split the function below into another function
 * if the `if() else if()` statements become too much
 * In that case I would call:
 * void	identify_keynum(t_level *level, t_mlx *mlx_data);
 *
 * NB: ESC == 65307
 * I will create enums for this later on (TODO)
*/

int	keyboard_handler(int keynum, void *voided_cub3d)
{
	t_cub3d	*cub3d;
	t_level	*level;
	t_mlx	*mlx_data;

	cub3d = (t_cub3d *) voided_cub3d;
	level = &cub3d->level;
	mlx_data = &cub3d->mlx_data;
	if (keynum == 65307)
		close_window(mlx_data->instance);
	else
		printf("Keynum \"%i\" has no handler\n", keynum);
	return (0);
}

void	hook_events(t_mlx *mlx_data, t_cub3d *cub3d)
{
	mlx_hook(mlx_data->window, ON_DESTROY, NO_EVENT_MASK,
		close_window, mlx_data->instance);
	mlx_hook(mlx_data->window, ON_KEYDOWN, NO_EVENT_MASK,
		keyboard_handler, cub3d);
}
