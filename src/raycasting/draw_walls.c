/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 13:13:50 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 13:15:17 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	draw_walls(t_textures *tex, t_level *level, t_img *frame)
{
	int			i;
	t_ray_utils	ray_utils;
	t_ray		ray;
	double		angle_step;
	double		angle_start;

	angle_step = (double) FOV / WINDOWLENGTH;
	angle_start = level->player_dir_deg - ((double) FOV / 2);
	i = 0;
	while (i < WINDOWLENGTH)
	{
		ray_utils.angle_deg = angle_start + (angle_step * i);
		shoot_ray(&ray, &ray_utils, level);
		draw_textured_line(i, &ray, tex, frame);
		i++;
	}
}
