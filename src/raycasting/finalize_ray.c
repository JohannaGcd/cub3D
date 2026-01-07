/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:16:44 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 11:38:10 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// TODO: Include fisheye correction.
// ray.length * cos(deg_to_rad(ray_utils.angle_deg - level->player_dir_deg));

void	finalize_ray(t_ray *ray, t_ray_utils *utils, int x_or_y)
{
	if (x_or_y == X)
	{
		if (utils->delta[X] > 0)
			ray->side = NO;
		else
			ray->side = SO;
		ray->pos_wall_hit = fmod(utils->pos[X], 1);
	}
	else
	{
		if (utils->delta[Y] > 0)
			ray->side = EA;
		else
			ray->side = WE;
		ray->pos_wall_hit = fmod(utils->pos[Y], 1);
	}
}
