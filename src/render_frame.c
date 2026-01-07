/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 10:57:15 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 13:22:04 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Upper half of screen must be filled with cub3d->ceiling colors (RGB)
//Lower half of screen must be filled with cub3d->floor colors (RGB)
//Function serves also as a frame wiper (wiping out the previous frame)

void	draw_floor_and_ceiling(t_cub3d *cub3d)
{
	void *f;
	void *c;

	f = my_mlx_rgb_converter(r, g, b);
	c = my_mlx_rgb_converter(r, g, b);
}

//Clear the frame (optional)
//Draw floor and ceiling.
//Shoot a ray for every column
//draw that ray to the screen with draw_textured_line.

void	render_frame(t_cub3d *cub3d, t_mlx *mlx_data)
{
	t_level		*level;
	t_img		*frame;
	t_textures	*tex;

	tex = &cub3d->texture;
	level = &cub3d->level;
	frame = &mlx_data->frame;
	draw_floor_and_ceiling();
	draw_walls(tex, level, frame);
	mlx_put_image_to_window(mlx_data->instance, mlx_data->window,
		frame->instance, 0, 0);
	return ;
}
