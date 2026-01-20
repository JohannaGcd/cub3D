/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:37:08 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/20 10:03:29 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	free_textures(t_textures *t, t_mlx *m)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (t->mlx_img[i].instance)
			my_mlx_destroy_image(m, &t->mlx_img[i]);
		i++;
	}
}

void	clean_up(t_mlx *m, t_cub3d *c)
{
	if (m->instance)
	{
		if (c)
			free_textures(&c->textures, m);
		if (m->window)
			my_mlx_destroy_window(m);
		if (m->frame.instance)
			my_mlx_destroy_image(m, &m->frame);
		my_mlx_destroy_display(m);
	}
	if (c)
		free_parser_data(c);
}
