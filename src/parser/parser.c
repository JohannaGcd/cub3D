# include "cub3d.h"

/*
* Main parser function - entry point for parsing .cub files.
* Orchestrates the 4 steps of the parsing process:
* 1. File reading (opens file, uses get_next_line)
* 2. Metadata parsing (parses textures and colors with bit flags)
* 3. Map parsing (dynamically grows map array)
* 4. Map validation (validates final map using flood fille)

* Returns:
* 0 on success
* -1 on error (with error messages printed)
* On error, frees all allocated memory before returning.
*/

int parse_cub_file(char *filename, t_cub3d *data)
{
    int fd;

    if (!filename || !data)
    {
        printf("Error\nInvalid arguments\n");
        return (-1);
    }
    if (!has_cub_extension(filename))
    {
        printf("Error\nFile must have .cub extension\n");
        return (-1);
    }
    init_cub3d_data(data),
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Error\nCannot open file");
        return (-1);
    }
    if (read_file_line_by_line(fd, data) == -1)
    {
        close(fd);
        free_oarser_data(data);
        return (-1);
    }
    close(fd);
    if (validata_map(data) == -1)
    {
        free_parser_data(data);
        return (-1);
    }
    return (0);
}