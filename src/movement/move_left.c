/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 15:24:42 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/13 15:26:31 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_left(t_level *level, long time_ms)
{
	double	angle_rad;
	double	time_s;

	time_s = time_ms / 1000.0;
	angle_rad = deg_to_rad(level->player_dir_deg + 90);
	move_player(level, time_s, angle_rad);
}
