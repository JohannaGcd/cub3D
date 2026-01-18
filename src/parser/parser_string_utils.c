/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_string_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jojo <jojo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/13 14:22:05 by jguacide          #+#    #+#             */
/*   Updated: 2026/01/18 13:15:24 by jojo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// free split? then replace in parse_rgb_value and split string
// ft_memcpy
// ft_strdup

char	*ft_strdup(const char *s1)
{
	char	*dup;
	size_t	len;
	size_t	i;

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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	**split_string(char *str, char delimiter)
{
	char	**result;
	int		count;
	int		i;
	int		start;

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
				break ;
		}
		i++;
	}
	result[count] = NULL;
	return (result);
}

char	*trim_whitespace(char *str)
{
	char	*start;
	char	*end;
	char	*trimmed;
	size_t	len;

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

