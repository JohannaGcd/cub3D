/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_left.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:25:03 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/13 15:26:41 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotate_left(t_level *level, long time_ms)
{
	double	new_dir;

	new_dir = level->player_dir_deg - (ROTATE_SPEED * time_ms / 1000.0);
	if (new_dir > 360)
		new_dir = fmod(new_dir, 360);
	if (new_dir < -360)
		new_dir = fmod(new_dir, 360);
	level->player_dir_deg = new_dir;
}
