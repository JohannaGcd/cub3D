/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:34:07 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/10 12:43:38 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	update_player_movement(long delta_t_ms, t_cub3d *cub3d)
{
	t_movement *move;
	t_level		*level;

	move = &cub3d->movement;
	level = &cub3d->level;
	(void) delta_t_ms;

	if (move->forward)
		move_forward(level, delta_t_ms);
	if (move->backward)
		printf("we would be moving backward\n");
	if (move->left)
		printf("we would be moving left\n");
	if (move->right)
		printf("right\n");
	if (move->rotate_left)
		printf("rot left\n");
	if (move->rotate_right)
		printf("rot right\n");
}

int	game_loop(t_cub3d *cub3d)
{
	static long	last_frame_time = 0;
	long		current_frame_time;
	long		delta_t_ms;

	if (last_frame_time == 0)
	{
		last_frame_time = get_time_ms();
		return (0);						//Technically unneccesary since we check whether delta_t == 0
	}
	current_frame_time = get_time_ms();
	delta_t_ms = current_frame_time - last_frame_time;
	//If no time passed at all (very unlikely)
	//we will just say 1ms has passed. I doubt 
	//people can see this.
	if (delta_t_ms == 0)
		return (0);
	update_player_movement(delta_t_ms, cub3d);
	render_frame(cub3d, cub3d->mlx_data);
	last_frame_time = current_frame_time;
	return (0);
}

