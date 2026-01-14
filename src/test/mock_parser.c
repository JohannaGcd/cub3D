/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mock_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:47:25 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/07 14:29:36 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

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
	result[2][6] = result[5][4] = '1';
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

void	shoot_ray_EA_SO_WE_NO(t_level *level)
{
	t_ray 		ray;
	t_ray_utils	u;

	u.angle_deg = 0;
	while (u.angle_deg < 360)	
	{
		shoot_ray(&ray, &u, level);
		printf("angle %f, length: %f\n", u.angle_deg, ray.length);
		printf("\tdeltaX %f, deltaY %f\n", u.delta[X], u.delta[Y]);
		u.angle_deg += 90;
	}
}

void	set_player_in_map(char **map, double x, double y)
{
	map[(int) y][(int) x] = 'P';
	printf("player is on location (x:%f, y:%f)\n", x, y);
}

void	set_level_values(t_level *level)
{
	level->map = create_square_test_map(10);
	level->x_row = 10;
	level->y_col = 10;
	level->player_pos_x = 5.8;
	level->player_pos_y = 5;
	level->player_dir_deg = 45.0;
	set_player_in_map(level->map, level->player_pos_x, level->player_pos_y);
}

void	print_map(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i] != NULL)
	{
		j = -1;
		while (map[i][++j] != '\0')
			printf("%c", map[i][j]);
		printf("\n");
	}
}

//Hardcode some textures to test with.
void	mock_texture_paths(t_textures *texture)
{
	texture->path[NO] = "./textures/cloud.xpm";
	texture->path[EA] = "./textures/cobble.xpm";
	texture->path[SO] = "./textures/sun.xpm";
	texture->path[WE] = "./textures/wood.xpm";
}

//Hardcoding the floor red and the ceiling blue.
void	set_floor_ceiling(t_cub3d *cub3d)
{
	cub3d->floor.r = 255;
	cub3d->floor.g = 12;
	cub3d->floor.b = 12;
	cub3d->ceiling.r = 12;
	cub3d->ceiling.g = 12;
	cub3d->ceiling.b = 255;
}

void	mock_parser(t_cub3d *data)
{
	
	set_level_values(&data->level);
	set_floor_ceiling(data);
	mock_texture_paths(&data->texture);
	print_map(data->level.map);
	//shoot_ray_EA_SO_WE_NO(&data->level);
}
