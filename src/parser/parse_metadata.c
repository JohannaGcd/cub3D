#include "cub3d.h"

int pars
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