/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out_of_bounds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 16:14:06 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 16:32:37 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	out_of_bounds(int x, int y, t_level *level)
{
	if (x > level->x_row || y > level->y_col)
		return (1);
	if (x < 0 || y < 0)
		return (1);
	return (0);
}
