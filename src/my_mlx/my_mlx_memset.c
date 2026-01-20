/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx_memset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 09:10:51 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/20 09:15:10 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	my_mlx_memset(t_mlx *m, t_textures *t)
{
	int	i;

	i = -1;
	while (++i < 4)
		t->mlx_img[i].instance = NULL;
	m->instance = NULL;
	m->window = NULL;
	m->frame.instance = NULL;
}
