/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   render_frame.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: zivanov <zivanov@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/07 10:57:15 by zivanov       #+#    #+#                 */
/*   Updated: 2026/01/13 15:45:59 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

//Upper half of screen must be filled with cub3d->ceiling colors (RGB)
//Lower half of screen must be filled with cub3d->floor colors (RGB)
//Function serves also as a frame wiper (wiping out the previous frame)

void	draw_floor_and_ceiling(t_cub3d *cub3d, t_img *frame)
{
	int	f;
	int	c;
	int	i;
	int	j;

	f = create_rgb(cub3d->floor.r, cub3d->floor.g, cub3d->floor.b);
	c = create_rgb(cub3d->ceiling.r, cub3d->ceiling.g, cub3d->ceiling.b);
	j = -1;
	while (++j < WINDOWHEIGHT / 2)
	{
		i = -1;
		while (++i < WINDOWLENGTH)
			my_mlx_pixel_put(frame, i, j, c);
	}
	while (j < WINDOWHEIGHT)
	{
		i = -1;
		while (++i < WINDOWLENGTH)
			my_mlx_pixel_put(frame, i, j, f);
		j++;
	}
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

	tex = &cub3d->textures;
	level = &cub3d->level;
	frame = &mlx_data->frame;
	draw_floor_and_ceiling(cub3d, frame);
	draw_walls(tex, level, frame);
	mlx_put_image_to_window(mlx_data->instance, mlx_data->window,
		frame->instance, 0, 0);
	return ;
}
