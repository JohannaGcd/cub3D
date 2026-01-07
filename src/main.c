/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:57:38 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 11:59:56 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

/*
 * Part of the main I can write for testing purposes only.
*/

static void test_main(t_mlx *mlx_data, t_cub3d *cub3d)
{
	//test_image(mlx_data, cub3d);
	render_frame(cub3d, mlx_data);
}

int	main(void)
{
	t_mlx	mlx_data;
	t_cub3d	cub3d;

	//PART OF THE TESTER!
	mock_parser(&cub3d);
	if (init_data(&mlx_data, &cub3d) != 0)
		return (-1);
	test_main(&mlx_data, &cub3d);
	hook_events(&mlx_data, &cub3d);
	mlx_loop(mlx_data.instance);
	//clean_up();
	return (0);
}
