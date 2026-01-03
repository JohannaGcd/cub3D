/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:09:49 by zivanov           #+#    #+#             */
/*   Updated: 2025/12/30 17:14:16 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
 * init for mlx_data to split the main init function.
 * creating:
 * 		- mlx_window
 * 		- mlx pointer
 * 		- setting window size
*/

static int	init_mlx(t_mlx *d)
{
	d->instance = mlx_init();
	if (d->instance == NULL)
		return (-1);
	d->win_h = WINDOWHEIGHT;
	d->win_l = WINDOWLENGTH;
	d->window = mlx_new_window(d->instance, d->win_l, d->win_h, "cub3d");
	if (d->window == NULL)
	{
		mlx_destroy_display(d->instance);
		return (-1);
	}
	return (0);
}

/*
 * Main initialization of all data for execution part.
 * This includes:
 * 		creation of mlx pointer.
 * 		creation of mlx_win pointer.
 * 		creation of mlx images to push to screen. //TODO
*/

int	init_data(t_mlx *mlx_data, t_cub3d *cub3d)
{
	if (init_mlx(mlx_data) != 0)
		return (-1);
	(void ) cub3d;
	return (0);
}
