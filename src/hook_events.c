/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_events.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:19:22 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/10 12:50:07 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	close_window(void *mlx_instance)
{
	mlx_loop_end(mlx_instance);
	return (0);
}

int	key_press_handler(int keynum, t_cub3d *cub3d)
{
	t_mlx		*mlx_data;

	printf("hel");
	mlx_data = cub3d->mlx_data;
	if (keynum == KEY_ESC)
		close_window(mlx_data->instance);
	else if (keynum == KEY_W)
		cub3d->movement.forward = 1;
	else if (keynum == KEY_S)
		cub3d->movement.backward = 1;
	else if (keynum == KEY_A)
		cub3d->movement.left = 1;
	else if (keynum == KEY_D)
		cub3d->movement.right = 1;
	else if (keynum == KEY_LEFT_ARROW)
		cub3d->movement.rotate_left = 1;
	else if (keynum == KEY_RIGHT_ARROW)
		cub3d->movement.rotate_right = 1;
	else
		printf("keynum: %i\n", keynum);
	return (0);
}

int	key_release_handler(int keynum, t_cub3d *cub3d)
{
	if (keynum == KEY_W)
		cub3d->movement.forward = 0;
	else if (keynum == KEY_S)
		cub3d->movement.backward = 0;
	else if (keynum == KEY_A)
		cub3d->movement.left = 0;
	else if (keynum == KEY_D)
		cub3d->movement.right = 0;
	else if (keynum == KEY_LEFT_ARROW)
		cub3d->movement.rotate_left = 0;
	else if (keynum == KEY_RIGHT_ARROW)
		cub3d->movement.rotate_right = 0;
	return (0);
}

void	hook_events(t_mlx *mlx_data, t_cub3d *cub3d)
{
	mlx_hook(mlx_data->window, ON_DESTROY, NO_EVENT_MASK,
		close_window, mlx_data->instance);
	mlx_hook(mlx_data->window, ON_KEYDOWN, KEY_PRESS_MASK,
		key_press_handler, cub3d);
	mlx_hook(mlx_data->window, ON_KEYUP, KEY_RELEASE_MASK,
		key_release_handler, cub3d);
}
