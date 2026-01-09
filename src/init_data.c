/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:09:49 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/09 17:02:04 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
 * init for mlx_data to split the main init function.
 * creating:
 * 		- mlx_window
 * 		- mlx pointer
 * 		- setting window size
 *
 * 		The `my_mlx_create_image` is somewhat vague;
 * 			- the instance variable holds the mlx instance
 *			- the frame variable holds the img structure
*/

static int	init_mlx(t_mlx *d)
{
	d->instance = mlx_init();
	if (d->instance == NULL)
	{
		perror("mlx_init fail\n");
		return (-1);
	}
	d->win_h = WINDOWHEIGHT;
	d->win_l = WINDOWLENGTH;
	d->window = mlx_new_window(d->instance, d->win_l, d->win_h, "cub3d");
	if (d->window == NULL)
	{
		perror("mlx_new_window failed\n");
		mlx_destroy_display(d->instance);
		return (-1);
	}
	my_mlx_create_image(d->instance, &d->frame, WINDOWLENGTH, WINDOWHEIGHT);
	if (d->frame.instance == NULL)
	{
		perror("my_mlx_create_image(frame) failed\n");
		mlx_destroy_window(d->instance, d->window);
		mlx_destroy_display(d->instance);
		return (-1);
	}
	return (0);
}

void	get_data_addr(t_img *img)
{
	img->addr = mlx_get_data_addr(img->instance, &img->bits_per_pixel,
		&img->line_length, &img->endian);
}

/*  * Loading of textures. We will specifically need .xpm files.
 *
 * TODO
 * It is currently uncertain whether failure of loading a 
 * texture is considered an error. It probably is, but we
 * can also try to use a color if no texture exists.
 * This means that in the rendering, we check whether the
 * instance for texture->img exists and if not, we simply
 * draw the side with a simple color.
*/

static int	init_textures(t_mlx *mlx, t_textures *t)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		t->mlx_img[i].instance = mlx_xpm_file_to_image(
			mlx->instance, t->path[i], &t->width[i], &t->height[i]);
		if (t->mlx_img[i].instance == NULL)
			perror("failure in init_textures\n");
		get_data_addr(&t->mlx_img[i]);
		i++;
	}
	return (0);
}

/*
 * Main initialization of all data for execution part.
 * This includes:
 * 		creation of mlx pointer.
 * 		creation of mlx_win pointer.
 * 		creation of mlx images to push to screen.
 * 		loading of textures
*/

int	init_data(t_mlx *mlx_data, t_cub3d *cub3d)
{
	if (init_mlx(mlx_data) != 0)
	{
		perror("init_mlx failed\n");
		return (-1);
	}
	cub3d->mlx_data = mlx_data;
	if (init_textures(mlx_data, &cub3d->texture) != 0)
	{
		perror("init_textures failed\n");
		return (-1);
	}
	return (0);
}
