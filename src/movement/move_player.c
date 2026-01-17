/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:35:26 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/17 15:24:05 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_player_dir(t_level *level, double deg_rot)
{
	printf("Player dir: %f\n", level->player_dir_deg);
	printf("Moving angle: %f\n", (deg_rot / M_PI) * 180);
}

/*
 * Note that because we consider the point (0.0) to be in the
 * top left corner, we get a -sin() for the y dimension!
 * This can be seen in shoot_ray.c (set_xy_pos_and_delta).
*/

void	move_player(t_level *level, double time_s, double angle_rad)
{
	double	new_x;
	double	new_y;

	new_x = level->player_pos_x + (cos(angle_rad) * VELOCITY * time_s);
	new_y = level->player_pos_y + -(sin(angle_rad) * VELOCITY * time_s);
	if (check_collision(level, (int) new_x, (int) level->player_pos_y) != 1)
		level->player_pos_x = new_x;
	if (check_collision(level, (int) level->player_pos_x, (int) new_y) != 1)
		level->player_pos_y = new_y;
}
