/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 16:34:07 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/09 17:30:18 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	game_loop(t_cub3d *cub3d)
{
	static long	last_frame_time = 0;
	long		current_frame_time;
	long		delta_t_ms;

	if (last_frame_time == 0)
	{
		last_frame_time = get_time_ms();
		return (0);						//Technically unneccesary since we check
	}
	current_frame_time = get_time_ms();
	delta_t_ms = current_frame_time - last_frame_time;
	//If no time passed at all (very unlikely)
	//we will just say 1ms has passed. I doubt 
	//people can see this.
	if (delta_t_ms == 0)
		return (0);
	//update_player_movement(cub3d);	TODO
	render_frame(cub3d, cub3d->mlx_data);
	last_frame_time = current_frame_time;
	return (0);
}

