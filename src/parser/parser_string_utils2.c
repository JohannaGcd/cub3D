/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_string_utils2.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: jguacide <jguacide@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2026/01/19 14:12:57 by jguacide      #+#    #+#                 */
/*   Updated: 2026/01/19 14:20:09 by jguacide      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../../inc/cub3d.h"

static size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;

	i = 0;
	len_src = ft_strlen(src);
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (len_src);
}

static size_t	check_allocation(char **tab, size_t i)
{
	size_t	j;

	if (tab[i] != NULL)
		return (0);
	j = 0;
	while (j < i)
		free(tab[j++]);
	free(tab);
	return (1);
}

static int	get_tab_len(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			len++;
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (len);
}

static int	get_word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

char	**split_string(char const *s, char c)
{
	size_t	i;
	char	**tab;
	size_t	word_len;
	size_t	tab_len;

	tab_len = get_tab_len(s, c);
	tab = (char **)malloc((tab_len + 1) * sizeof(char *));
	if (tab == NULL)
		return (NULL);
	tab[tab_len] = NULL;
	i = 0;
	while (i < tab_len)
	{
		while (*s == c)
			s++;
		word_len = get_word_len(s, c);
		tab[i] = (char *)malloc((get_word_len(s, c) + 1) * sizeof(char));
		if (check_allocation(tab, i) == 1)
			return (NULL);
		ft_strlcpy(tab[i], s, word_len + 1);
		s += word_len;
		i++;
	}
	return (tab);
}