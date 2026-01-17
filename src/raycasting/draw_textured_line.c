/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textured_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 15:32:25 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/17 15:33:38 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//Need to think how to do this correctly but basically
//if the distance is 1, the wall gets drawn completely 
//to the screen. If the distance is smaller we get to see
//a fraction of the wall (just like you don't see the whole
//screen of your computer when you are 2cm away from it)

static void	convert_length_to_pixels(double length, int *pixels)
{
	if (length <= 0.0)
		*pixels = WINDOWHEIGHT;
	*pixels = WINDOWHEIGHT / length;
	if (*pixels > WINDOWHEIGHT * 9)
		*pixels = WINDOWHEIGHT * 9;
	else if (*pixels < 1)
		*pixels = 1;
}

/*
 * Another annoying function. But frighten not.
 * Suppose the line we want to draw is 100 pixels long,
 * but our image only has 50x50 pixels. We fix this by
 * adding a stepsize. We calculate the stepsize
 * beforehand since it is the same for the whole line.
 * This function just gives you the y_index for which
 * pixel to grab from your texture!
 *
 * So we want to know what color from the texture we pick
 * to draw our current pixel from.
*/

static int	calc_y(int j, int pixels, double stepsize, int max_pixels)
{
	int	result;

	result = (j + ((double) pixels / 2)) * stepsize;
	if (result >= max_pixels)
		return (max_pixels - 1);
	else if (result < 0)
		return (0);
	return (result);
}

/*
 * Some weird stuff is happening here.
 * We have to think on how we count in our
 * frame. Conceptually we would consider the
 * origin to be in the middle of our screen/frame
 * but we start counting from the upper left corner.
 * Thus the middle of the screen really is position
 * (WINDOWWIDTH / 2, WINDOWHEIGHT / 2)
 *
 * If we draw from the middle of the line, we want to shoot 
 * part of the ray down and part of the ray up. Otherwise
 * we would get an amsterdam view of the canal houses.
 * This is a bit tricky to visualize using only words.
*/

void	draw_textured_line(int row, t_ray *ray, t_textures *tex, t_img *frame)
{
	int				tex_x;
	int				tex_y;
	double			stepsize;
	unsigned int	color;
	int				j;

	convert_length_to_pixels(ray->length, &ray->pixels);
	if (ray->pixels <= 0)
		return ;
	j = -(ray->pixels / 2);
	tex_x = ray->pos_wall_hit * tex->width[ray->side];
	if (tex_x >= tex->width[ray->side])
		tex_x = tex->width[ray->side] - 1;
	stepsize = (double) tex->height[ray->side] / ray->pixels;
	while (j < (ray->pixels / 2))
	{
		tex_y = calc_y(j, ray->pixels, stepsize, tex->height[ray->side]);
		color = my_mlx_get_pixel_color(&tex->mlx_img[ray->side], tex_x, tex_y);
		if ((WINDOWHEIGHT / 2) + j > WINDOWHEIGHT - 1
			|| (WINDOWHEIGHT / 2) + j < 0)
			;
		else
			my_mlx_pixel_put(frame, row, (WINDOWHEIGHT / 2) + j, color);
		j++;
	}
}
