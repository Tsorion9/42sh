/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_ifs_chars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:55:38 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 17:55:48 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static size_t	count_space_chars(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == ' ' || !ft_isprint(s[i]))
			count++;
		i++;
	}
	return (count);
}

static size_t	count_delimiter_chars(const char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != ' ' && ft_isprint(s[i]))
			count++;
		i++;
	}
	return (count);
}

void			fill_space_ifs(char **s_ifs, const char *ifs)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	j = 0;
	size = count_space_chars(ifs);
	*s_ifs = ft_strnew(size);
	while (ifs[i])
	{
		if (ifs[i] == ' ' || !ft_isprint(ifs[i]))
			(*s_ifs)[j++] = ifs[i];
		i++;
	}
}

void			fill_delimiters_ifs(char **d_ifs, const char *ifs)
{
	int		i;
	int		j;
	size_t	size;

	i = 0;
	j = 0;
	size = count_delimiter_chars(ifs);
	*d_ifs = ft_strnew(size);
	while (ifs[i])
	{
		if (ifs[i] != ' ' && ft_isprint(ifs[i]))
			(*d_ifs)[j++] = ifs[i];
		i++;
	}
}
