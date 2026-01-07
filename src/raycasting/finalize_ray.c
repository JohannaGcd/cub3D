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

// The last calculation done in this function is to fix the fisheye effect.
// ray.length * cos(deg_to_rad(ray_utils.angle_deg - level->player_dir_deg));

void	finalize_ray(t_ray *ray, t_ray_utils *utils, int x_or_y, t_level *l)
{
	if (x_or_y == X)
	{
		if (utils->delta[X] > 0)
			ray->side = NO;
		else
			ray->side = SO;
		ray->pos_wall_hit = fmod(utils->pos[Y], 1);
	}
	else
	{
		if (utils->delta[Y] > 0)
			ray->side = EA;
		else
			ray->side = WE;
		ray->pos_wall_hit = fmod(utils->pos[X], 1);
	}
	ray->length *= cos(deg_to_rad(utils->angle_deg - l->player_dir_deg));
}
