/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:07:41 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 16:17:02 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	set_xy_pos_and_delta(t_ray_utils *utils, t_level *level)
{
	utils->pos[X] = level->player_pos_x;
	utils->pos[Y] = level->player_pos_y;
	utils->delta[X] = cos(deg_to_rad(utils->angle_deg));
	utils->delta[Y] = -sin(deg_to_rad(utils->angle_deg));
}

static void	set_xy_ds_and_next(t_ray_utils *utils)
{
	utils->next[X] = find_gridline(utils->pos[X], utils->delta[X]);
	utils->ds[X] = utils->next[X] / utils->delta[X];
	utils->next[Y] = find_gridline(utils->pos[X], utils->delta[Y]);
	utils->ds[Y] = utils->next[X] / utils->delta[Y];
}

void	shoot_ray(t_ray *ray, t_ray_utils *u, t_level *level)
{
	set_xy_pos_and_delta(u, level);
	while (true)
	{
		set_xy_ds_and_next(u);
		if (fabs(u->delta[X]) > fabs(u->delta[Y]))
		{
			ray->length += fabs(u->ds[Y]);
			u->pos[Y] += u->next[Y];
			u->pos[X] += u->ds[Y] * u->delta[X];
			if (detect_wall_hori(u, level))
				return (finalize_ray(ray, u, Y));
		}
		else
		{
			ray->length += fabs(u->ds[X]);
			u->pos[X] += u->next[X];
			u->pos[Y] += u->ds[X] * u->delta[Y];
			if (detect_wall_vert(u, level))
				return (finalize_ray(ray, u, X));
		}
	}
}
