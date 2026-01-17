/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_map_to_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/17 12:32:20 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/17 12:35:59 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	convert_map_to_level(t_cub3d *cub3d)
{
	t_level	*l;
	t_map	*m;

	l = &cub3d->level;
	m = &cub3d->map;
	l->map = m->grid;
	l->y_col = m->width;
	l->x_row = m->height;
	l->player_pos_x = m->player_x;
	l->player_pos_y = m->player_y;
	if (m->player_dir == 'N')
		l->player_dir_deg = 90.0;
	if (m->player_dir == 'E')
		l->player_dir_deg = 0.0;
	if (m->player_dir == 'S')
		l->player_dir_deg = 270.0;
	if (m->player_dir == 'W')
		l->player_dir_deg = 180.0;
}
