/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:36:58 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/20 09:42:54 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_destroy_window(t_mlx *m)
{
	if (m->instance && m->window)
	{
		mlx_destroy_window(m->instance, m->window);
		m->window = NULL;
	}
}

void	my_mlx_destroy_display(t_mlx *m)
{
	if (m->instance)
	{
		mlx_destroy_display(m->instance);
		free(m->instance);
		m->instance = NULL;
	}
}

void	my_mlx_destroy_image(t_mlx *m, t_img *img)
{
	if (img->instance && m->instance)
	{
		mlx_destroy_image(m->instance, img->instance);
		img->instance = NULL;
	}
}
