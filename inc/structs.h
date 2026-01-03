/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:05:59 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 15:56:32 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "enums.h"
// --- --- --- S T R U C T U R E S --- --- ---
// - - - - - - - - - - - - - - - - - - - - - -
// (because we can't pass a hundred
// 		parameters to a function)

/*	-- MLX STRUCTURE --
 * Simple structure holding relevant data
 * for the graphical library mlx.
 * 
 * Main usage of the library is
 * the creation and maintenance 
 * of windows, events and images

 * More info on this library can be found
 * in the mlx/mlx.h header.
 *
 * The win_h and win_l parameters
 * are for future resizing of windows.
 * This is not a subject requirement,
 * but perhaps useful just in case.
*/

typedef struct s_mlx
{
	void	*instance;
	void	*window;
	int		win_h;
	int		win_l;
}	t_mlx;

/*	-- LEVEL STRUCTURE --
 * Metadata of the level given from the parser.
 * Should contain:
 * 		- The map.
 * 		- Starting position player
 * 		- Colors for Floor & ceiling
*/

typedef struct s_level
{
	char	**map;
	int		x_row;
	int		y_col;
	int		player_pos_x;
	int		player_pos_y;
	int		player_dir_deg;
}	t_level;

/*
 * -- TEXTURE STRUCTURE --
 *  Paths will be given by parsing.
 *  Execution will create the mlx image structures.
 *  This can be considered part of the mlx structure,
 *  yet this was purposely avoided to make a
 *  distinction between the mlx instance and the mlx images.
 *
 *  This structure makes use of the t_dir enums and can be used
 *  as following: textures.paths[NO/EA/SO/WE] and
 *  similarly textures.mlx_img[NO/EA/SO/WE]
 *
 *  TODO: When loading in an image I will need to know
 *  their width and height for the raytracing.
*/

typedef struct s_textures
{
	char	*paths[4];
	void	*mlx_img[4];
	int		width[4];
	int		height[4];
}	t_textures;

/*
 * -- RAY STRUCTURE --
 * If we weren't working with textures,
 * the only relevant part of the ray would be its
 * length and we wouldn't need this structure,
 * however since we ARE working with textures we
 * need to know a little more about every ray we shoot:
 * 		- Where on the wall did the ray hit?
 * 		- Which side of the wall did we hit?
 * 	NB: We could also combine the two by having a float
 * 	that has the wall side when we convert to int and has
 * 	the pos on the wall when we take the fmod(x, 1).
 * 	(1.34 would be side 1 (EA) and pos_wall_hit .34)
*/

typedef struct s_ray
{
	double	length;
	double	pos_wall_hit;
	t_dir	side;
}	t_ray;

/*
 * -- RAY UTILS STRUCTURE --
 * These variables are important for calculating
 * the ray but not necessarily the ray itself.
 *
 * To effectively pass all variables as one
 * parameter, this structure is created. (thanks norminette)
 *
 * angle_deg; the degree in which the ray is heading (unit circle).
 * pos; the current position of the ray (starts at player pos).
 * delta; the respective direction of X and X (dependant on the angle)
 * ds; distance of the ray before hitting a X/Y gridline.
 * next_gridline; distance (for X/Y) to the next gridline from current X/Y pos.
 *
*/

typedef struct s_ray_utils
{
	double	angle_deg;
	double	pos[2];
	double	delta[2];
	double	ds[2];
	double	next[2];
}	t_ray_utils;
/*
 * -- COLOR STRUCTURE --
 *  In essence this is a simple array of three integers
 *  yet to avoid the confusion of pointers and arrays
 *  a decision was made to use a separate structure.
 *
 *  This makes parsing colors as a parameter easier and more readable.
 *  Instead of `some_func(int colors[3]);`
 *  (above can be confusing when using pointers and arrays combined)
 *  we can use `some_func(t_colors *colors);`
 *  (this is a pointer and not an array)
*/

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_colors;

/*
 * -- CUB3D STRUCTURE --
 *  A big meta structure that holds all the
 *  data needed for the cub3d program to run.
 *  Most structures have their descriptions given
 *  in the comments above.
*/

typedef struct s_cub3d
{
	t_textures	texture;
	t_colors	floor;
	t_colors	ceiling;
	t_mlx		mlx_data;
	t_level		level;
}	t_cub3d;
#endif
