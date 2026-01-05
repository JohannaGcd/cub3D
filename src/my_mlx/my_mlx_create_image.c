/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_create_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 10:05:02 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/05 10:14:07 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_create_image(void *mlx, t_img *img, int width, int height)
{
	img->instance = mlx_new_image(mlx, width, height);
	if (img->instance == NULL)
		return ;
	img->addr = mlx_get_data_addr(img->instance, &img->bits_per_pixel,
			&img->line_length, &img->endian);
}
