/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_file_reader.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/13 14:22:12 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/19 13:13:53 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

#define BUFFER_SIZE 1024

/*
 * Reads from file descriptor and writes into buffer:
 * Read returns: bytes_read on success, 0 if nothing was read, -1 if error
 * Adds NULL terminating character at the end of the buffer before returning.
 */
static char	*read_buffer(int fd, char *buffer, int *bytes_read)
{
	*bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (*bytes_read < 0)
		return (NULL);
	buffer[*bytes_read] = '\0';
	return (buffer);
}

/*
 * Extract a complete line from buffer:
 * Advances *pos until after the '\n'
 * Returns the allocated strings containing the line (including '\n')
 */
static char	*extract_line(char *buffer, int *pos)
{
	char	*line;
	int		start;
	int		len;

	start = *pos;
	while (buffer[*pos] && buffer[*pos] != '\n')
		(*pos)++;
	len = *pos - start;
	if (buffer[*pos] == '\n')
		(*pos)++;
	line = malloc(sizeof(char) * (len + 2));
	if (!line)
		return (NULL);
	len = 0;
	while (start < *pos)
		line[len++] = buffer[start++];
	line[len] = '\0';
	return (line);
}

/*
 * File reading infrastructure:
 * Returns line from fd each time is it called,
 * Uses a static buffer to store what is read from the file
 * And remembers position in that file using static variables,
	persistent between function calls.
 */
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	static int	pos = 0;
	static int	bytes_read = 0;
	char		*line;

	if (fd < 0)
		return (NULL);
	if (pos >= bytes_read || buffer[pos] == '\0')
	{
		if (!read_buffer(fd, buffer, &bytes_read))
		{
			if (bytes_read == 0 && pos == 0)
				return (NULL);
		}
		pos = 0;
		if (bytes_read == 0)
			return (NULL);
	}
	line = extract_line(buffer, &pos);
	return (line);
}
