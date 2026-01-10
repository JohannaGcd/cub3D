/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 12:35:26 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/10 12:41:22 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	move_forward(t_level *level, long time)
{
	double	new_x;
	double	new_y;
	double	angle_rad;

	angle_rad = deg_to_rad(level->player_dir_deg);
	new_x = level->player_pos_x + (cos(angle_rad) * VELOCITY * time);
	new_y = level->player_pos_y + (sin(angle_rad) * VELOCITY * time);

	//Check wall collision before assigning new values
	level->player_pos_x = new_x;
	level->player_pos_y = new_y;
	return ;
}
