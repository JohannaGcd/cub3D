/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:57:15 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 11:38:10 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Clear the frame (optional)
//Draw floor and ceiling.
//Shoot a ray for every column
//draw that ray to the screen with draw_textured_line.
//TODO>: Norminette proof

void	render_frame(t_cub3d *cub3d, t_mlx *mlx_data)
{
	double		angle_step;
	double		angle_start;
	t_level		*level;
	t_ray		ray;
	t_ray_utils	ray_utils;
	t_img		*frame;
	int			i;
	t_textures	*tex;

	level = &cub3d->level;
	frame = &mlx_data->frame;
	tex = &cub3d->texture;

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
	mlx_put_image_to_window(mlx_data->instance, mlx_data->window,
		frame->instance, 0, 0);
	return ;
}
