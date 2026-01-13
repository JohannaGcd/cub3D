/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:22:05 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/13 15:57:18 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// free split? then replace in parse_rgb_value and split string
// ft_memcpy
// ft_strdup

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
        str++;
    }
    while (*str >= '0' && *str <= '9')
    {
        result = result * 10 + (*str - '0');
        str++;
    }
    return (result * sign);
}

void    ft_intset(int *array, int value, int len)
{
    int i;

    i = 0;
    while (i < len)
    {
        array[i] = value;
        i++;
    }
}

char    *ft_strdup(const char *s1)
{
    char    *dup;
    size_t  len;
    size_t  i;

    len = ft_strlen(s1);
    dup = malloc(sizeof(char) * (len + 1));
    if (!dup)
        return (NULL);
    i = 0;
    while (i <= len)
    {
        dup[i] = s1[i];
        i++;
    }
    return (dup);
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

void    *ft_memcpy(void *dest, const void *src, size_t len)
{
    size_t  i;

    i = 0;
    while (i < len)
    {
        ((char *)dest)[i] = ((char *)src)[i];
        i++;
    }
    return (dest);
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
                while (count-- > 0)
                    free(result[count]);
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

bool    is_valid_map_char(char c)
{
    return (c == '0' || c == '1' || c == 'N' || c == 'S' 
        || c == 'W' || c == 'E' || c == ' ' || c == '\t');
}
void    free_parser_data(t_cub3d *data)
{
    int i;
    
    if (!data)
        return;
    i = 0;
    while (i < 4)
    {
        free(data->textures.path[i]);
        data->textures.path[i] = NULL;
        i++;
    }
    if (data->map.grid)
    {
        i = 0;
        while (data->map.grid[i])
        {
            free(data->map.grid[i]);
            i++;
        }
        free(data->map.grid);
        data->map.grid = NULL;
    }
}