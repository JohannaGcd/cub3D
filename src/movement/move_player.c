/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:35:26 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/13 15:27:08 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	move_player(t_level *level, double time_s, double angle_rad)
{
	double	new_x;
	double	new_y;

	new_x = level->player_pos_x + (cos(angle_rad) * VELOCITY * time_s);
	new_y = level->player_pos_y +  (sin(angle_rad) * VELOCITY * time_s);
	if (check_collision(level, (int) new_x, (int) new_y))
	{
		printf("WALL COLLISIONS!\n");
		return ;
	}
	level->player_pos_x = new_x;
	level->player_pos_y = new_y;
}
