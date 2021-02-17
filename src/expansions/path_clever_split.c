/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_clever_split.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:29:09 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:29:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static int		is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

static size_t	count_fields(const char *s, char delim)
{
	size_t	size;
	int		i;
	int		in_quote;

	size = 0;
	i = -1;
	in_quote = 0;
	while (s[++i] != '\0')
	{
		if (s[i] != delim)
		{
			size++;
			while ((s[i] != '\0' && s[i] != delim) || in_quote)
			{
				if (is_quote(s[i]))
					in_quote ^= s[i];
				i++;
			}
			if (s[i] == '\0')
				return (size);
		}
	}
	return (size);
}

static size_t	count_len_sub_path(const char *s, size_t *i, char delim)
{
	size_t	len;
	int		in_quote;

	len = 0;
	in_quote = 0;
	while ((s[*i] != '\0' && s[*i] != delim) || in_quote)
	{
		if (is_quote(s[*i]))
			in_quote ^= s[*i];
		len++;
		(*i)++;
	}
	return (len);
}

static void		fill_fields(char ***splitted_fields, char delim, const char *s)
{
	size_t	size;
	size_t	i;
	size_t	len;
	int		idx;

	i = 0;
	idx = 0;
	size = count_fields(s, delim);
	(*splitted_fields) = (char**)ft_memalloc(8 * (size + 1));
	while (s[i] != '\0')
	{
		if (s[i] != delim)
		{
			len = count_len_sub_path(s, &i, delim);
			(*splitted_fields)[idx++] = ft_strsub(s, i - len, len);
			if (s[i] == '\0')
				return ;
		}
		i++;
	}
	(*splitted_fields)[idx] = NULL;
}

/*
** Split path by '/' character
** return malloced 2-dimensional array of sub-paths of path without '/' char
*/

char			**path_clever_split(const char *path)
{
	char	**splitted_path;

	if (!path || *path == '\0')
		return (NULL);
	splitted_path = NULL;
	fill_fields(&splitted_path, '/', path);
	return (splitted_path);
}
