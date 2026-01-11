#include "cub3d.h"

/*
* Parses RGB values from string format "R,G,B"
* - splits by comma
* - converts to int
* - validates each value is between 0 and 255
*/
static int  parse_rgb_value(char *rgb_str, t_colors *color)
{
    char    **parts;
    int     r, g, b;

    parts = split_string(rgb_str, ',');
    if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
    {
        if (parts)
        {
            int i = 0;
            while (parts[i])
                free(parts[i++]);
            free(parts);
        }
        printf("Error\nInvalid RGB format. Expected: R,G,B\n");
        return (-1);
    }
    r = ft_atoi(parts[0]);
    g = ft_atoi(parts[1]);
    b = ft_atoi(parts[2]);
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        int i = 0;
        while (parts[i])
            free(parts[i++]);
        free(parts);
        printf("Error\nRGB values must be between 0 and 255\n");
        return (-1);
    }
    color->r = r;
    color->g = g;
    color->b = b;

    int i = 0;
    while (parts[i])
        free(parts[i++]);
    free(parts);
    return (0);
}
/*
* Parses a color line (F or C)
* - Checks for duplicates using bit flag ('&')
* - Extracts RGB string
* - Parses and validates RGB values
* - Sets bit flag ('|=')
*/
int parse_color(char *line, t_cub3d *data, t_meta_flags flag)
{
    char        *color_str;
    t_colors    *color_ptr;

    if (data->metadata_flags & flag)
    {
        printf("Error\nDuplicate color definition\n");
        return (-1);
    }
    if (flag == META_F)
        color_ptr = &data->floor;
    else if (flag == META_C)
        color_ptr = &data->ceiling;
    else
        return (-1);
    color_str = extract_path(line, 2);
    if (!color_str || ft_strlen(color_str) == 0)
    {
        printf("Error\nInvalid color format\n");
        free(color_str);
        return (-1);
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
static char *extract_path(char *line, int skip_len)
{
    char    *path;
    char    *start;
    char    *trimmed;

    start = line + skip_len;
    skip_spaces(&start);
    if (!*start || *start == '\n')
        return (NULL);
    trimmed = trim_whitespace(start);
    return (trimmed);
}
/*
* Parses a texture line
* - Checks for duplicates using bit flag ('& flag' is the 'and' operator)
* - Extracts path after identifier (NO, SO, WE or EA)
* - Validates path is not empty
* - Sets bit flag when successful ('|= flag' is the 'or' operator)
*/
int parse_texture(char *line, t_cub3d *data, t_meta_flags flag, t_dir dir)
{
    char    *path;

    if (data->metadata_flags & flag)
    {
        printf("Error\nDuplicate texture definition\n");
        return (-1);
    }
    path = extract_path(line, 3);
    if (!path || ft_strlen(path) == 0)
    {
        printf("Error\nInvalid texture path\n");
        free(path);
        return (-1);
    }
    data->textures.paths[dir] = path;
    data->metadata_flags |= flag;
    return (0);
}
int parse_metadata_line(char *line, t_cub3d *data, int line_num)
{
    char *trimmed;

    trimmed = trim_whitespace(line);
    if (!trimmed || is_empty_line(trimmed))
    {
        free(trimmed);
        return (0);
    }
    if (ft_strncmp(trimmed, "NO ", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, META_NO, NO));
    }
    else if (ft_strncmp(trimmed, "SO ", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, META_SO, SO));
    }
    else if (ft_strncmp(trimmed, "WE ", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, META_WE, WE));
    }
    else if (ft_strncmp(trimmed, "EA ", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, META_EA, EA));
    }
    else if (ft_strncmp(trimmed, "F ", 2) == 0)
    {
        free(trimmed);
        return (parse_color(line, data, META_F));
    }
    else if (ft_strncmp(trimmed, "C ", 2) == 0)
    {
        free(trimmed);
        return (parse_color(line, data, META_C));
    }
    free(trimmed);
    printf("Error\nInvalid metadata line at line %d\n", line_num);
    return (-1);
}