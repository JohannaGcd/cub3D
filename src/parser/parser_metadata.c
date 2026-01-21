/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_metadata.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:22:07 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/21 17:40:37 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

/*
 * Parses RGB values from string format "R,G,B"
 * - splits by comma
 * - converts to int
 * - validates each value is between 0 and 255
 */
static int	parse_rgb_value(char *rgb_str, t_colors *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = split_string(rgb_str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
	{
		if (parts)
			free_split(parts);
		return (ft_error("Invalid RGB format. Expected: R,G,B"));
	}
	if (ft_isdigit(parts[0]) != 0 || ft_isdigit(parts[1]) != 0
		|| ft_isdigit(parts[2]) != 0)
		return (ft_error("RGB values must be between 0 and 255"));
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (free_split(parts),
			ft_error("RGB values must be between 0 and 255"));
	color->r = r;
	color->g = g;
	color->b = b;
	return (free_split(parts), 0);
}

static char	*extract_path(char *line, int skip_len)
{
	char	*start;
	char	*trimmed;

	start = line + skip_len;
	skip_spaces(&start);
	if (!*start || *start == '\n')
		return (NULL);
	trimmed = trim_whitespace(start);
	return (trimmed);
}

/*
 * Parses a color line (F or C)
 * - Checks for duplicates using bit flag ('&')
 * - Extracts RGB string
 * - Parses and validates RGB values
 * - Sets bit flag ('|=')
 */
int	parse_color(char *line, t_cub3d *data, t_meta_flags flag)
{
	char		*color_str;
	t_colors	*color_ptr;

	if (data->metadata_flags & flag)
		return (ft_error("Duplicate color definition"));
	if (flag == META_F)
		color_ptr = &data->floor;
	else if (flag == META_C)
		color_ptr = &data->ceiling;
	else
		return (-1);
	color_str = extract_path(line, 2);
	if (!color_str || ft_strlen(color_str) == 0)
	{
		free(color_str);
		return (ft_error("Invalid color format"));
	}
	if (parse_rgb_value(color_str, color_ptr) == -1)
	{
		free(color_str);
		return (-1);
	}
	free(color_str);
	data->metadata_flags |= flag;
	return (0);
}

/*
 * Parses a texture line
 * - Checks for duplicates using bit flag ('& flag' is the 'and' operator)
 * - Extracts path after identifier (NO, SO, WE or EA)
 * - Validates path is not empty
 * - Sets bit flag when successful ('|= flag' is the 'or' operator)
 */
int	parse_texture(char *line, t_cub3d *data, t_meta_flags flag, t_dir dir)
{
	char	*path;

	if (data->metadata_flags & flag)
		return (ft_error("Duplicate texture definition"));
	path = extract_path(line, 3);
	if (!path || ft_strlen(path) == 0)
		return (ft_error("Invalid texture path"));
	data->textures.path[dir] = path;
	data->metadata_flags |= flag;
	return (0);
}

int	parse_metadata_line(char *line, t_cub3d *data)
{
	char	*trimmed;

	trimmed = trim_whitespace(line);
	if (!trimmed || is_empty_line(trimmed))
		return (free(trimmed), 0);
	if (ft_strncmp(trimmed, "NO ", 3) == 0)
		return (free(trimmed), parse_texture(line, data, META_NO, NO));
	else if (ft_strncmp(trimmed, "SO ", 3) == 0)
		return (free(trimmed), parse_texture(line, data, META_SO, SO));
	else if (ft_strncmp(trimmed, "WE ", 3) == 0)
		return (free(trimmed), parse_texture(line, data, META_WE, WE));
	else if (ft_strncmp(trimmed, "EA ", 3) == 0)
		return (free(trimmed), parse_texture(line, data, META_EA, EA));
	else if (ft_strncmp(trimmed, "F ", 2) == 0)
		return (free(trimmed), parse_color(line, data, META_F));
	else if (ft_strncmp(trimmed, "C ", 2) == 0)
		return (free(trimmed), parse_color(line, data, META_C));
	free(trimmed);
	return (ft_error("Invalid metadata"));
}
