/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_rgb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/07 14:04:55 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 14:16:36 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	create_rgb(int r, int g, int b)
{
	int	result;

	r = r & 0xFF;
	g = g & 0xFF;
	b = b & 0xFF;
	result = (r << 16) | (g << 8) | b;
	return (result);
}
