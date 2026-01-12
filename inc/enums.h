/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:07:04 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/12 20:02:32 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUMS_H
# define ENUMS_H
// --- --- --- E N U M S --- --- --- ---
// - - - - - - - - - - - - - - - - - - -
// (the bridge between readable
// 		and executable code)

/*
 * X11 Masking events. (very difficult and somewhat beyond the scope)
 * These enums are used with 
 * bit operators to specify what device we are getting input from.
 * In essence, this can be the keyboard or the mouse.
 * 
 * There is an important destinction between KEY_PRESS and KEY_RELEASE:
 * When holding down a key, we will first send a single
 * key press and after half a second start spamming this key.
 * (you can easily see this in any text editor when holding down a key)
 *
 * This makes movement (in f.e. a videogame) stuttered:
 * you move a little, then stand still and start moving again.
 *
 * Thus we need to combine both KEYPRESS and a KEYRELEASE event;
 * one to start the movement and one to stop it.
*/

typedef enum e_mask
{
	NO_EVENT_MASK = 0L,
	KEY_PRESS_MASK = (1L << 0),
	KEY_RELEASE_MASK = (1L << 1),
	BUTTON_PRESS_MASK = (1L << 2),
	STRUCTURE_NOTIFY_MASK = (1L << 17)
}	t_mask;

/*
 * X11 Events with their corresponding values.
 * In addition to the masking, these enums are used to 
 * identify what kind of event is triggered in 
 * the mlx_hook() function.
 * (see hook_events.c)
 * for more documentation see:
 * https://harm-smits.github.io/42docs/libs/minilibx/events.html
*/

typedef enum e_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEMOVE = 6,
	ON_DESTROY = 17
}	t_events;

/*
 * X11 Key codes. This is for readability.
 * When a key is pressed we don't have
 * to memorize the keycode. 
 * WASD are for movement, ESC for exiting
 * and LEFT and RIGHT for rotating.
*/

typedef enum e_keynums
{
	KEY_ESC = 65307,
	KEY_W = 119,
	KEY_A = 97,
	KEY_S = 115,
	KEY_D = 100,
	KEY_LEFT_ARROW = 65361,
	KEY_RIGHT_ARROW = 65363
}	t_keynums;

/*
 * To make the texture structure more readable
 * we use a simple enum to keep track of
 * which side of the cube we are talking about.
 * Usage would be:
 * cub3d->textures.paths[NO];
*/

typedef enum e_dir
{
	NO = 0,
	EA = 1,
	SO = 2,
	WE = 3
}	t_dir;

/*
* Metadata flags used by the parser to track
* which required elements have been encountered so far.
* These are bit flags (one bit inside an integer which we use as an "on/off switch") 
* They can be combined into an integer, ALL_METADATA
*/
typedef enum e_metadata_flags
{
	META_NO = (1 << 0), // 000001 -> 1
	META_SO = (1 << 1), // 000010 -> 2
	META_WE = (1 << 2), // 000100 -> 3
	META_EA = (1 << 3), // 001000 -> 8
	META_F = (1 << 4),  // 010000 -> 16
	META_C = (1 << 5)   // 100000 -> 32
}	t_meta_flags;

# define ALL_METADATA (META_NO | META_SO | META_WE | META_EA | META_F | META_C)

#endif
