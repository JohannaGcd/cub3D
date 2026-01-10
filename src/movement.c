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

int	check_collision(t_level *level, int x, int y)
{
	if (x < 0 || y < 0 || x > level->x_row || y > level->y_col)
		return (1);
	if (level->map[y][x] == '1')
		return (1);
	return (0);
}

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

void	move_forward(t_level *level, long time_ms)
{
	double	angle_rad;
	double	time_s;

	time_s = time_ms / 1000.0;
	angle_rad = deg_to_rad(level->player_dir_deg);
	move_player(level, time_s, angle_rad);
}

void	move_backward(t_level *level, long time_ms)
{
	double	angle_rad;
	double	time_s;

	time_s = time_ms / 1000.0;
	angle_rad = deg_to_rad(level->player_dir_deg + 180);
	move_player(level, time_s, angle_rad);
}

void	move_right(t_level *level, long time_ms)
{
	double	angle_rad;
	double	time_s;

	time_s = time_ms / 1000.0;
	angle_rad = deg_to_rad(level->player_dir_deg + 90);
	move_player(level, time_s, angle_rad);
}

void	move_left(t_level *level, long time_ms)
{
	double	angle_rad;
	double	time_s;

	time_s = time_ms / 1000.0;
	angle_rad = deg_to_rad(level->player_dir_deg + 270);
	move_player(level, time_s, angle_rad);
}

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

void	rotate_right(t_level *level, long time_ms)
{
	double	new_dir;

	new_dir = level->player_dir_deg + (ROTATE_SPEED * time_ms / 1000.0);
	if (new_dir > 360)
		new_dir = fmod(new_dir, 360);
	if (new_dir < -360)
		new_dir = fmod(new_dir, 360);
	level->player_dir_deg = new_dir;
}
