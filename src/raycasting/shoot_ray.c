/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 13:07:41 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 11:33:49 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * We modify the position of the ray.
 * While they all share the same starting condition
 * the values get modified as we trace the ray.
 * Thus I deem it wise to set the starting
 * position in this function.
*/

static void	set_xy_pos_and_delta(t_ray_utils *utils, t_level *level)
{
	utils->pos[X] = level->player_pos_x;
	utils->pos[Y] = level->player_pos_y;
	utils->delta[X] = cos(deg_to_rad(utils->angle_deg));
	utils->delta[Y] = -sin(deg_to_rad(utils->angle_deg));
}

//Potential bug in set_xy_ds_and_next [FIXED]
//What if deltaX or deltaY is close to 0 (aka we only travel in one direction)
//I'll tell you: Dividing by 0 leads to complications for utils->dsX/Y

static void	set_xy_ds_and_next(t_ray_utils *utils)
{
	utils->next[X] = find_gridline(utils->pos[X], utils->delta[X]);
	if (utils->delta[X] == 0)
		utils->ds[X] = INFINITY;
	else
		utils->ds[X] = utils->next[X] / utils->delta[X];
	utils->next[Y] = find_gridline(utils->pos[Y], utils->delta[Y]);
	if (utils->delta[Y] == 0)
		utils->ds[Y] = INFINITY;
	else
		utils->ds[Y] = utils->next[Y] / utils->delta[Y];
}

/*
 * I can not stress this enough. Be aware of Cartesian notation
 * and matrix/programming notation. Matrix[Y][X] stands for
 * Cartesian point (X,Y). I use macro's for readability.
 * Please check in the header what values the macro's for X and Y have
 * when debugging the program. Otherwise this might lead to
 * some serious confusion!
*/

void	shoot_ray(t_ray *ray, t_ray_utils *u, t_level *level)
{
	ray->length = 0;
	set_xy_pos_and_delta(u, level);
	while (true)
	{
		set_xy_ds_and_next(u);
		if (fabs(u->ds[X]) > fabs(u->ds[Y]))
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
