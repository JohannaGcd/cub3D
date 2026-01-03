/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_next_gridline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/31 10:59:40 by zivanov           #+#    #+#             */
/*   Updated: 2025/12/31 12:25:22 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*	
 * --- --- --- READ ME --- --- ---
 * I wrote a very long explanation by giving
 * two examples that we need to consider in this
 * function. The function itself is not that difficult
 * in terms of code but it the trick is to visualize,
 * understand and apply it to the scenario of raycasting.
 * 
 * I recommend only reading the following if the code
 * does not make any bloody sense to you.
 *
 * (EXPLANATION)
 * This is a one dimensional function;
 * in the context of cub3d this means we 
 * temporarily reduce a plane to a line.
 * In mathematical terms this means we look at 
 * only 1 of the 2 axis (so either x or y axis).
 *
 * Say we are on a line and have gridlines at
 * every integer (1, 2, 3, ...). If on this line
 * our current position is 4.35, our two next
 * gridlines would be at 4 or 5.
 *
 * This function calculates what value we need to
 * subtract or add in order to get to this gridline.
 * In our current example this would be -0.35 or 0.65
 *
 * Say our position is 4.35.
 *
 * The first calculation translates to:
 * fmod(4.35, 1) = 0.35
 * -1 * fmod(4.35, 1) = -1 * 0.35 = -0.35;
 *
 *  This is one of the possible next gridlines
 *  (or the distance to get there)
 *  (a negative distance means we travel backwards)
 *
 *  result != 0 so we can skip this codeblock.
 *  
 *  If our direction happened to be positive 
 *  (the ray travels forward), then our next
 *  gridline would be 0.65. Well...
 *  result = -0.35 + 1 = 0.65;
 *
 *  There you have it!
 *
 *
 *  Now let's say we are on position 3.0
 *  The next gridline is either 2.0 or 4.0.
 *
 *	fmod(3.0, 1) = 0;
 *	result = -1 * fmod(3.0, 1) = -1 * 0 = 0;
 *
 *	Well we know the next gridline is not 0,
 *	so this is wrong. Which is why we have the
 *	following check:
 *
 *	if (result == 0)
 *		result = 1;
 *	
 *	We know the result is either going to 1 or -1.
 *
 *	if (dir < 0) (if we are travelling backwards)
 *		result = -1;
 *
 *	And that is about all this function does!
*/

double	find_gridline(double pos, double dir)
{
	double	result;

	result = -1 * fmod(pos, 1);
	if (result == 0)
	{
		result = 1;
		if (dir < 0)
			result = -1;
	}
	else if (dir > 0)
		result += 1;
	return (result);
}
