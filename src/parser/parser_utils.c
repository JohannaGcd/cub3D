#include "cub3d.h"

// split string
// atoi
// free split? then replace in parse_rgb_value

bool    is_empty_line(char *line)
{
    if (!line)
        return (true);
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n')
            return (false);
        line++;
    }
    return (true);
}
size_t  ft_strlen(const char *s)
{
    size_t  len;

    len = 0;
    while(s[len])
        len++;
    return (len);
}

int ft_strncmp(const char *s1, const char *s2, size_t n)
{
    size_t  i;

    if (n == 0)
        return (0);
    i = 0;
    while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void    skip_spaces(char **line)
{
    if (!line || !*line)
        return;
    while (**line == ' ' || **line == '\t')
        (*line)++;
}

char    *trim_whitespace(char *str)
{
    char    *start;
    char    *end;
    char    *trimmed;
    size_t  len;

    if (!str)
        return (NULL);
    start = str;
    while (*start == ' ' || *start == '\t')
        start++;
    if (*start == '\0')
        return (ft_strdup(""));
    end = start;
    while (*end && *end != '\n')
        end++;
    while (end > start && (*(end - 1) == ' ' || *(end - 1) == '\t'))
        end--;
    len = end - start;
    trimmed = malloc(sizeof(char) * (len + 1));
    if (!trimmed)
        return (NULL);
    trimmed[len] = '\0';
    while (len-- > 0)
        trimmed[len] = start[len];
    return (trimmed);
}
void    free_parser_data(t_cub3d *data)
{
    int i;
    
    if (!data)
        return;
    if (data->textures.north)
        free(data->textures.north);
    if (data->textures.south)
        free(data->textures.south);
    if (data->textures.west)
        free(data->textures.west);
    if (data->textures.east)
        free(data->textures.east);
    if (data->map.grid)
    {
        i = 0;
        while (data->map.grid[i]);
        {
            free(data->map.grid[i]);
            i++;
        }
        free(data->map.grid)
    }

}