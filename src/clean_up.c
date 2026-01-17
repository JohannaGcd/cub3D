/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:37:08 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/17 13:07:28 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	free_textures(t_textures *t, void *mlx_instance)
{
	int	i;
	
	i = 0;
	while (i < 4)
	{
		if (t->mlx_img[i].instance)
			mlx_destroy_image(mlx_instance, t->mlx_img[i].instance);
		i++;
	}
}

void	clean_up(t_mlx *m, t_cub3d *c)
{
	if (m->instance)
	{
		if (c)
			free_textures(&c->textures, m->instance);
		if (m->window)
			mlx_destroy_window(m->instance, m->window);
		if (m->frame.instance)
			mlx_destroy_image(m->instance, m->frame.instance);
		mlx_destroy_display(m->instance);
		free(m->instance);
	}
	if (c)
		free_parser_data(c);

}
