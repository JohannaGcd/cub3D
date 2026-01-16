/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_collision.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:14:28 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/13 15:23:24 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//TODO Needs to be implemented more rigurous. 
//Currently lets a lot of textures through that cannot be rendered.

int	check_collision(t_level *level, int x, int y)
{
	if (x < 0 || y < 0 || x > level->x_row || y > level->y_col)
		return (1);
	if (level->map[y][x] == '1')
		return (1);
	return (0);
}
