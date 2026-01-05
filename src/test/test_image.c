/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 11:26:27 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/05 11:28:47 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	print_square_on_frame(t_mlx *mlx, t_img *frame)
{
	int		i;
	int		j;

	for (i = 0; i < 100; i++)
	{
		for (j = 0; j < 100; j++)
		{
			my_mlx_pixel_put(frame, i, j, RED);
		}
	}
	mlx_put_image_to_window(mlx->instance, mlx->window, frame->instance, 400, 400);
}

void	test_image(t_mlx *mlx_data)
{
	print_square_on_frame(mlx_data, &mlx_data->frame);
	return ;
}
