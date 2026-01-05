/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 11:07:29 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/05 10:33:13 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../mlx/mlx.h"
# include "enums.h"
# include "structs.h"
# include <math.h>
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

// - - - - M A C R O S - - - -
// - - - - - - - - - - - - - -
// (basically constant global variables)

// Some can be changed to reconfigure certain aspects of the game.
// NOTE: This will require a rebuild.

// Dimensions of the window for the game.
# define WINDOWLENGTH 1920
# define WINDOWHEIGHT 1080

//I like to use an array holding the X and the Y value of something.
//Coming from a mathematical background, I prefer the first value
//to be X and the second value to be Y when separating the two.
//(because that is also how we learned to work with vectors)
//
//So: position[2] would hold the x value in 
//position[0] and y in position[1]
# define X 0
# define Y 1

//--- --- --- F U N C T I O N S --- --- ---
//- - - - - - - - - - - - - - - - - - - - -
// (prototypes and descriptions of
// 		all nonstatic functions)
// 	NB: If no description is given assume
// 		its usage is considered very
// 		straightforward or the developer
// 		was too lazy...

//ALL data for the executive part gets initialized here. Most of the stuff
//is mlx related and can probably use better naming.
//handles the instance of mlx, the window pointer, the image creation.
//NOTE: A specific distinction is made between the image textures
//		and the mlx metadata. See the relevant structures for more explanation.
int		init_data(t_mlx *data, t_cub3d *cub3d);

//ONLY FOR TESTING WITHOUT PARSING
//This is just for Zachaar to develop raytracing before the 
//parser is (completely) finished.
void	mock_parser(t_cub3d *cub3d);

// Events are actions a user can perform in the game. They range from
// keypresses (wasd) to mouse movement to pressing the 'x' button onscreen.
// In simple terms we connect input from the player to the
// corresponding action. (we hook events to specific functions)
void	hook_events(t_mlx *mlx_data, t_cub3d *cub3d);

// -- RAYCASTING FUNCTIONS --
// Functions relevant for the casting of rays and
// can be found in the raycasting folder.

// The following function finds the next gridline for either
// the x or the y direction. A more detailed description of
// this function can be found in the file find_gridline.c
double	find_gridline(double pos, double dir);

// Shoots a ray untill it hits a wall using the DDA algorithm.
void	shoot_ray(t_ray *ray, t_ray_utils *u, t_level *level);

// If the ray hits a wall (on either the x or the y side)
// we update the ray with some final parameters. (where the wall
// was hit, which side of the wall was hit etc)
void	finalize_ray(t_ray *ray, t_ray_utils *utils, int x_or_y);

// This is a safety check to see whether the position in the map
// we are trying to access/check actually exists (in case we
// somehow skipped the NULL terminator)
int		out_of_bounds(int x, int y, t_level *level);

// Wall detection. We split into a horizontal wall checker and
// a vertical wall checker. We need to take the direction into
// account since if we are travelling into a negative direction
// we want to check one gridsquare back.
int		detect_wall_hori(t_ray_utils *utils, t_level *level);
int		detect_wall_vert(t_ray_utils *utils, t_level *level);

// -- MATH UTILS --

//Cos() and sin() functions work with radians, humans are known to use degrees
//I like degrees because I never had one, so I prefer to think in degrees
//and then convert to radians when needed.
double	deg_to_rad(double degree);

// -- MY MLX FUNCTIONS --
// Functions to either make working with the mlx library easy or functional.

// The infamous pixel_put function from Harm Smits' github! What does
// this function do? Well, from what I understand, this is primarily 
// an optimization technique. Instead of pushing every pixel to the 
// screen, we place pixels on an image (one big pixel matrix) and
// then push that image to the screen. Thus this really needs no
// usage of any mlx functions. It merely sets the color of a pixel
// on an image. You can sort of compare it to image_matrix[y][x] = color.
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

// This is more a lazy function. It calls the mlx_get_data_addr after initializing.
// so:			mlx_create_image -> mlx_get_data_addr. 
// Because we create quite alot of images (for the textures), this is a way to
// some lines and headspace.
//
// NB: The data addres is of high importance due to
// the my_mlx_pixel_put function.
//
// PS: the mlx instance pointer is wanted here. Not the mlx window pointer.
void	my_mlx_create_image(void *mlx, t_img *img, int width, int height);

#endif
