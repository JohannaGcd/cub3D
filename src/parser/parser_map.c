/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_map.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:22:09 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/13 16:30:30 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

/*
* Detects if a line is a valid map line, ie:
* Contains valid map characters (0,1,N,S,E,W) or whitespaces
*/
bool    is_map_line(char *line)
{
    int     i;
    bool    has_map_char;

    if (!line)
        return (false);
    i = 0;
    has_map_char = false;
    while (line[i] && line[i] != '\n')
    {
        if (line[i] == '0' || line[i] == '1' || line[i] == 'N'
            || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
            has_map_char = true;
        else if (line[i] != ' ' && line[i] != '\t')
                return (false);
        i++;
    }
    printf("\nRETURN FROM is map line\n");
    return (has_map_char);
}

/*
* Grows map array by adding a new line at each pass.
* - First line: initialises map array with size 2 (for the line and NULL);
* - Subsequent lines: Reallocates array, copies existing lines, adds new line
*/
void    build_map(t_map  *map, char *line)
{
    char    **new_map;
    int     i;
    char    *line_copy;

    if (!map || !line)
        return;
    line_copy = ft_strdup(line);
    printf("line_copy in build map: %s", line_copy);
    if (!line_copy)
        return;
    if (map->grid == NULL)
    { 
        map->grid = malloc(sizeof(char *) * 2);
        if (!map->grid)
        {
            free(line_copy);
            return;
        }
        map->grid[0] = line_copy;
        map->grid[1] = NULL;
        map->height = 1;
        return;
    }
    new_map = malloc(sizeof(char *) * (map->height + 2));
    if (!new_map)
    {
        free(line_copy);
        return;
    }
    i = 0;
    while (i < map->height)
    {
        new_map[i] = map->grid[i];
        printf("in loop, new_map[%d] is %s", i, new_map[i]);
        i++;
    }
    new_map[i] = line_copy;
    new_map[i + 1] = NULL;
    free(map->grid);
    map->grid = new_map;
    map->height++;
}

void    calculate_map_dimensions(t_map *map)
{
    int max_width;
    int i;
    int len;

    max_width = 0;
    i = 0;
    while (map->grid[i])
    {
        len = ft_strlen(map->grid[i]);
        if (map->grid[i][len - 1] == '\n')
            len--;
        if (len > max_width)
            max_width = len;
        i++;
    }
    map->width = max_width;
}

/*
* Finds player's starting position in the map.
* - Scans the entire map for N,S,E,W characters
* - Records coordinates and direction. 
* - Adds '+ (1 / 2)' to place the player in the center of the square
* - Replaces player char with '0' in map
* - Validate that there is exactly one player
*/
int find_player_position(t_cub3d *data)
{
    int x;
    int y;
    int player_count;

    player_count = 0;
    y = 0;
    while (data->map.grid[y])
    {
        x = 0;
        while (data->map.grid[y][x])
        {
            if (data->map.grid[y][x] == 'N' || data->map.grid[y][x] == 'S'
                || data->map.grid[y][x] == 'E' || data->map.grid[y][x] == 'W')
            {
                if (player_count == 1)
                {
                    printf("Error\nMultiple player positions found\n");
                    return (-1);
                }
                data->map.player_x = x + (1 / 2);
                data->map.player_y = y + (1 / 2);
                data->map.player_dir = data->map.grid[y][x];
                data->map.grid[y][x] = '0';
                player_count++;
            }
            x++;
        }
        y++;
    }
    if (player_count == 0)
    {
        printf("Error\nNo player position found\n");
        return (-1);
    }
    return (0);
}