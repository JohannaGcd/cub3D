/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_wall.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:13:04 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 16:30:04 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * NB: Cartesian coordinate (X, Y) is located at
 * map[Y][X].
*/

int	detect_wall_vert(t_ray_utils *utils, t_level *level)
{
	int	x;
	int	y;

	x = (int) utils->pos[X];
	y = (int) utils->pos[Y];
	if (out_of_bounds(x, y, level))
		return (1);
	if (utils->delta[X] > 0)
		return (level->map[y][x] == '1');
	else
		return (level->map[y][x - 1] == '1');
}

int	detect_wall_hori(t_ray_utils *utils, t_level *level)
{
	int	x;
	int	y;

	x = (int) utils->pos[X];
	y = (int) utils->pos[Y];
	if (out_of_bounds(x, y, level))
		return (1);
	if (utils->delta[Y] > 0)
		return (level->map[y][x] == '1');
	else
		return (level->map[y - 1][x] == '1');
}
