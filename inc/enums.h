/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enums.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 17:07:04 by zivanov           #+#    #+#             */
/*   Updated: 2026/01/02 13:27:55 by zivanov          ###   ########.fr       */
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
#endif
