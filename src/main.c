/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:57:38 by zivanov           #+#    #+#             */
/*   Updated: 2025/12/30 17:14:16 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	main(void)
{
	t_mlx	mlx_data;
	t_cub3d	cub3d;

	if (init_data(&mlx_data, &cub3d) != 0)
		return (-1);
	mock_parser(&cub3d);
	hook_events(&mlx_data, &cub3d);
	mlx_loop(mlx_data.instance);
	//clean_up();
	return (0);
}
