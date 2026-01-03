/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zivanov <zivanov@student.codam.nl>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 13:47:25 by zivanov           #+#    #+#             */
/*   Updated: 2025/12/28 13:58:07 by zivanov          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static char	*first_or_last_row(int size)
{
	char	*result;
	int		i;

	if (size == 0)
		return (NULL);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = '\0';
	i = -1;
	while (++i < size)
		result[i] = '1';
	return (result);
}

static char	*middle_row(int size)
{
	char	*result;
	int		i;

	i = -1;
	if (size == 0)
		return (NULL);
	result = malloc(sizeof(char) * size + 1);
	if (result == NULL)
		return (NULL);
	while (++i < size)
	{
		if (i == 0 || i == size - 1)
			result[i] = '1';
		else
			result[i] = '0';
	}
	return (result);
}

static char	**create_square_test_map(int size)
{
	char	**result;
	int		i;

	i = -1;
	result = malloc(sizeof(char *) * size + 1);
	if (result == NULL)
		return (NULL);
	result[size] = NULL;
	while (++i < size)
	{
		if (i == 0 || i == size - 1)
			result[i] = first_or_last_row(size);
		else
			result[i] = middle_row(size);
		if (result[i] == NULL)
			exit(EXIT_FAILURE);
	}
	result[5][5] = 'N';
	//TODO remove for loop. Only for current debugging purposes
	for (i = 0; i < size; i++)
		printf("%s\n", result[i]);
	return (result);
}

void	mock_parser(t_cub3d *data)
{
	data->level.map = create_square_test_map(10);
}
