#include "../../inc/cub3d.h"

/*
* Checks each map character, one by one.
* returns an error if an unauthorized character is met.
*/
int validate_characters(t_cub3d *data)
{
    int y;
    int x;

    y = 0;
    while (data->map.grid[y])
    {
        x = 0;
        while (data->map.grid[y][x] && data->map.grid[y][x] != '\n')
        {
            if (!is_valid_map_char(data->map.grid[y][x]))
            {
                printf("Error\nInvalidate character '%c' at position (%d, %d)\n", data->map.grid[y][x], y, x);
                return (-1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

/*
* Tries to open each texture file.
* Returns -1 upon error.
*/
int validate_texture_files(t_cub3d *data)
{
    int fd;

    if (!data->textures.north)
        return (-1);
    fd = open(data->textures.north, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open texture file: %s\n", data->textures.north)
        return (-1);
    }
    close(fd);
    fd = open(data->textures.south, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open texture file: %s\n", data->textures.south)
        return (-1);
    }
    close(fd);
    fd = open(data->textures.west, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open texture file: %s\n", data->textures.west)
        return (-1);
    }
    close(fd);
    fd = open(data->texture.east, O_RDONLY);
    if (fd == -1)
    {
        printf("Error\nCannot open texture file: %s\n", data->textures.east)
        return (-1);
    }
    close(fd);
    return (0);
}

/*
* Helper function for flood_fill implementation
* to measure the length of the line.
*/
static int  get_line_width(char *line)
{
    int len;

    if (!line)
        return (0);
    len = 0;
    while (line[len] && line[len] != '\n')
        len++;
    return (len);
}
/*
* Recursive function for flood fill:
* Base case: checks if outside of boundaries (rows, then columns)
* Marks cell as visited
* Calls itself with the next index is all directions (y + 1 and y - 1, same for x);
*/
static int  flood_fill_recursive(char **map, int **visited, int x, int y, int height)
{
    int line_width;

    if (x < 0 || x >= height || !map[x])
        return (1);
    line_width = get_line_width(map[x]);
    if (y < 0 || y >= line_width)
        return (1);
    if (visited[x][y] || map[x][y] == '1')
        return (0);
    if (map[x][y] == ' ' || map[x][y] == \'n' || map[x][y] == '\0')
        return (1);
    visited[x][y] = 1;
    if (flood_fill_recursive(map, visited, x, y + 1, height))
        return (1);
     if (flood_fill_recursive(map, visited, x, y - 1, height))
        return (1); 
     if (flood_fill_recursive(map, visited, x + 1, y, height))
        return (1);
     if (flood_fill_recursive(map, visited, x - 1, y, height))
        return (1);
    return (0);
}
/*
* Flood fill tutorial: https://www.youtube.com/watch?v=RjO-HDjRMpM
* Create a visited array to track positions which have already been checked (avoids infinite loop)
* Start flood fill from player position
* If flood fill reaches boundaries, map is not closed (returns an error)
*/
int flood_fill_validation(t_cub3d *data)
{
    int **visited;
    int x;
    int result;

    visited = malloc(sizeof(int *) * data->map.height);
    if (!visited)
    {
        printf("Error\nMemory allocation failed\n");
        return (-1);
    }
    x = 0;
    while (x < data->map.height)
    {
        visited[x] = malloc(sizeof(int) * data->map.width);
        if (!visited[x])
        {
            while (x-- > 0)
                free(visited[x]);
            free(visited);
            return (-1);
        }
        memset(visited[x], 0, sizeof(int) * data->map.width); // FORBIDDEN FUNCTION, USE LIBFT
        x++;
    }
    result = flood_fill_recursive(data->map.grid, visited,
        data->player_x, data->player_y, data->map.height);
    
        x = 0;
    while(x < data->map.height)
        free(visited[x++]);
    free(visited);

    if (result)
    {
        printf("Error\nMap is not properly enclosed by walls\n");
        return (-1);
    }
    return (0);
}

/*
* Main validation function, which orchestrates each step:
* - Validates that there are only authorised map chars
* - Map should be enclosed (using flood fill)
* - Texture files should all exist and be readable
* Returns -1 upon error, 0 on success
*/
int validate_map(t_cub3d *data)
{
    if (validate_characters(data) == -1)
        return (-1);
    if (flood_fill_validation(data) == -1)
        return (-1);
    if (validate_texture_files(data) == -1)
        return (-1);
    return (0);
}