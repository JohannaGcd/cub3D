/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_misc_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 13:10:18 by jojo          #+#    #+#                 */
/*   Updated: 2026/01/19 17:47:25 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

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

void	ft_intset(int *array, int value, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		array[i] = value;
		i++;
	}
}

void	free_dbl_ptr(int	**arr, int count)
{
	int i;

	i = 0;
	if (!arr)
		return;
	while (i < count)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	skip_spaces(char **line)
{
	if (!line || !*line)
		return ;
	while (**line == ' ' || **line == '\t')
		(*line)++;
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

int	ft_error(char *error_str)
{
	printf("Error\n%s\n", error_str);
	return (-1);
}

int	ft_error_detail(char *error_str, char *detail)
{
	printf("Error\n%s: %s\n", error_str, detail);
	return (-1);
}
