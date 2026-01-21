/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils_misc.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: jojo <jojo@student.42.fr>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/18 13:10:18 by jojo          #+#    #+#                 */
/*   Updated: 2026/01/21 17:41:44 by jguacide      ########   odam.nl         */
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
int	ft_isdigit(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] <= '0' || str[i] >= '9')
			return (1);
		i++;
	}
	return (0);
}