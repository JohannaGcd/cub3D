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

int	detect_wall_vert(t_ray_utils *utils, t_level *level)
{
	int	x;
	int	y;

	x = (int) utils->pos[X];
	y = (int) utils->pos[Y];
	if (out_of_bounds(x, y, level))
		return (0);
	if (utils->delta[X] > 0)
		return (level->map[x][y] == '1');
	else
		return (level->map[x - 1][y] == '1');
}

int	detect_wall_hori(t_ray_utils *utils, t_level *level)
{
	int	x;
	int	y;

	x = (int) utils->pos[X];
	y = (int) utils->pos[Y];
	if (out_of_bounds(x, y, level))
		return (0);
	if (utils->delta[Y] > 0)
		return (level->map[x][y] == '1');
	else
		return (level->map[x][y - 1] == '1');
}
