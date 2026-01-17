/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:14:28 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/17 15:34:56 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/* I want to create better wall detection by giving 
 * the player a bigger hitbox. Essentially making the player
 * a square instead of a point. I think a dimension of 0.2x0.2
 * is big enough. Thus I need to check what direction we are 
 * facing (whether we are going backward or forward, since
 * that differs whether we extract or subtract 0.1 from
 * the new position)
 *
 * This means that instead of checking a single point,
 * we check four points (each of the corners).
*/

int	point_collision(t_level *level, int x, int y)
{
	if (x < 0 || y < 0 || x > level->x_row || y > level->y_col)
		return (1);
	if (level->map[y][x] == '1')
		return (1);
	return (0);
}

int	check_collision(t_level *level, double x, double y)
{
	double	offset;

	offset = 0.2;
	if (point_collision(level, x + offset, y) == 1)
		return (1);
	if (point_collision(level, x - offset, y) == 1)
		return (1);
	if (point_collision(level, x, y + offset) == 1)
		return (1);
	if (point_collision(level, x, y - offset) == 1)
		return (1);
	return (0);
}
