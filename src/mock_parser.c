/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:47:25 by zivanov           #+#    #+#             */
/*   Updated: 2025/12/28 13:58:07 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*first_or_last_row(int size)
{
	char	*result;
	int		i;

	if (size == 0)
		return (NULL);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	i = -1;
	while (++i < size)
		result[i] = '1';
	return (result);
}

static char	*middle_row(int size)
{
	char	*result;
	int		i;

	i = -1;
	if (size == 0)
		return (NULL);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	while (++i < size)
	{
		if (i == 0 || i == size - 1)
			result[i] = '1';
		else
			result[i] = '0';
	}
	return (result);
}

//create_square_test_map
//
//Nota Bene: Matrices in Programming languages are different from
//Cartesian coordination (which is often used in mathematics/physics). 
//In mathematics we (usually) first describe X and then Y. 
//A point in space would be (X, Y). But in C, the way pointers work, 
//we first specify the row (Y) and then the column (X).
//Thus some_matrix[Y][X] is equivalent to the Cartesian point (X, Y).

static char	**create_square_test_map(int size)
{
	char	**result;
	int		i;

	i = -1;
	result = malloc(sizeof(char *) * size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	while (++i < size)
	{
		if (i == 0 || i == size - 1)
			result[i] = first_or_last_row(size);
		else
			result[i] = middle_row(size);
		if (result[i] == NULL)
			exit(EXIT_FAILURE);
	}
	result[1][5] = result[5][4] = '1';
	result[5][5] = 'N';
	//TODO remove for loop. Only for current debugging purposes
	for (i = 0; i < size; i++)
		printf("%s\n", result[i]);
	return (result);
}

/* shoot_rayEA_SO_WE_NO
 * TODO BUG:
 * For some reason the raycaster is off by 90 degr.
 * I can quickly "fix" this by subtracting 90 degrees when
 * calling the raytracer but it makes me question whether
 * I am doing something funamentally wrong.
 *
 * Here is what I expect:
 * 0 degrees -> shooting ray to the right.
 * 		- deltaX = 1, deltaY = 0;
 * 90 degrees -> shooting ray completely up.
 * 		- deltaX = 0, deltaY = -1;
 * 180 degrees -> shooting ray to the left.
 * 		- deltaX = -1, deltaY = 0;
 * 270 degrees -> shooting ray completely down.
 * 		- deltaX = 0, deltaY = 1;
*/

void	shoot_ray_EA_SO_WE_NO(t_ray *ray, t_ray_utils *u, t_level *level)
{
	u->angle_deg = 0;
	while (u->angle_deg < 360)	
	{
		shoot_ray(ray, u, level);
		printf("angle %f, length: %f\n", u->angle_deg, ray->length);
		printf("\tdeltaX %f, deltaY %f\n", u->delta[X], u->delta[Y]);
		u->angle_deg += 90;
	}
}

void	mock_parser(t_cub3d *data)
{
	data->level.map = create_square_test_map(10);
	data->level.x_row = 10;
	data->level.y_col = 10;
	data->level.player_pos_x = 5.8;
	data->level.player_pos_y = 5;
	data->level.player_dir_deg = 90.0;
	t_ray ray_test;
	t_ray_utils utils_test;
	if (data->level.map
			[(int) data->level.player_pos_x]
			[(int) data->level.player_pos_y] == 'N')
		printf("player is on location (x:%f, y:%f)\n",
			data->level.player_pos_x, data->level.player_pos_y);
	shoot_ray_EA_SO_WE_NO(&ray_test, &utils_test, &data->level);
}
