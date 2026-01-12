#include "cub3d.h"

// free split? then replace in parse_rgb_value and split string
// ft_memcpy

int ft_atoi(const char *str)
{
    int sign;
    int result;

    sign = 1;
    result = 0;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
    {
        if (*str == '-')
            sign = -1;
        str++:
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0')
        str++:
    }
    return (result * sign);
}

char    **split_string(char *str, char delimiter)
{
    char    **result;
    int     count;
    int     i;
    int     start;

    if (!str)
        return (NULL);
    
    count = 1;
    i = 0;
    while (str[i])
    {
        if (str[i] == delimiter)
            count++;
        i++;
    }
    result = malloc(sizeof(char *) * (count + 1));
    if (!result)
        return (NULL);
    
    i = 0;
    start = 0;
    count = 0;
    while (1)
    {
        if (str[i] == delimiter || str[i] == '\0')
        {
            result[count] = malloc(sizeof(char) * (i - start + 1));
            if (!result[count])
            {
                while (j-- > 0)
                    free(result[j])
                free(result);
                return (NULL);
            }
            ft_memcpy(result[count], str + start, i - start);
            result[count][i - start] = '\0';
            count++;
            start = i + 1;
            if (str[i] == '\0')
                break;
        }
        i++;
    }
    result[count] = NULL;
    return (result);
}

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