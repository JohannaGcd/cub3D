#include "cub3d.h"

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

void    free_parer_data(t_cub3d *data)
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