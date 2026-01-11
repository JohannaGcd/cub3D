#include "cub3d.h"

static int  parse_rgb_value(chr *rgb_str)
int parse_color(char *line, t_cub3d *data, int flag)
{
    char        *color_str;
    t_colors    *color_ptr;

    if (data->metadata_flags & flag)
    {
        printf("Error\nDuplicate color definition\n");
        return (-1):
    }
    if (flag == F)
        color_ptr = &data->floor;
    else if (flag == C)
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
int parse_texture(char *line, t_cub3d *data, int flag)
{
    char    *path;
    char    **texture_ptr;

    if (data->metadata_flags & flag)
    {
        printf("Error\nDuplicate texture definition\n");
        return (-1);
    }
    if (flag == NO)
        texture_ptr = &data->texture.north;
    if (flag == SO)
        texture_ptr = &data->texture.south;
    if (flag == WE)
        texture_ptr = &data->texture.west;
    if (flag == EA)
        texture_ptr = &data->texture.east;
    else
        return (-1);
    path = extract_path(line, 3);
    if (!path || ft_strlen(path) == 0)
    {
        printf("Error\nIvalid texture path\n");
        free(path);
        return (-1);
    }
    *texture_ptr = path;
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
    if (ft_strncmp(trimmed, "NO", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, NO));
    }
    else if (ft_strncmp(trimmed, "SO", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, SO));
    }
    else if (ft_strncmp(trimmed, "WE", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, WE));
    }
    else if (ft_strncmp(trimmed, "EA", 3) == 0)
    {
        free(trimmed);
        return (parse_texture(line, data, EA));
    }
    else if (ft_strncmp(trimmed, "F", 2) == 0)
    {
        free(trimmed);
        return (parse_color(line, data, F));
    }
    else if (ft_strncmp(trimmed, "C", 2) == 0)
    {
        free(trimmed);
        return (parse_color(line, data, C));
    }
    free(trimmed);
    printf("Error\nInvalid metadata line at line %d\n", line_num);
    return (-1);
}