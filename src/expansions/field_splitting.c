/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   field_splitting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 16:06:41 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:10:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environment.h"
#include "parser.h"

/*
** Считает количество полей, на которое надо разбить строку s
*/

static int		count_fields(const char *s, char *s_ifs, char *d_ifs)
{
	int		size;
	size_t	i;

	size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!is_ifs_char(s[i], s_ifs) && !is_ifs_char(s[i], d_ifs))
		{
			size++;
			while (s[i] != '\0' && !is_ifs_char(s[i], s_ifs)
								&& !is_ifs_char(s[i], d_ifs))
				i++;
			if (s[i] == '\0')
				return (size);
			skip_ifs_chars(s, &i, s_ifs, d_ifs);
		}
		while (is_ifs_char(s[i], s_ifs))
			i++;
		while (is_ifs_char(s[i], d_ifs) && ++i)
			size++;
	}
	return (size);
}

static size_t	count_not_ifs_len(const char *s, size_t *i,
							const char *s_ifs, const char *d_ifs)
{
	size_t	len;

	len = 0;
	while (s[*i] != '\0' && !is_ifs_char(s[*i], s_ifs)
						&& !is_ifs_char(s[*i], d_ifs))
	{
		len++;
		(*i)++;
	}
	return (len);
}

static void		fill_fields(char ***fields, const char *src, char *s_ifs,
						char *d_ifs)
{
	size_t	len;
	size_t	i;
	int		size;
	int		idx;

	size = count_fields(src, s_ifs, d_ifs);
	*fields = (char**)ft_memalloc(sizeof(char*) * (size + 1));
	i = 0;
	idx = 0;
	while (src[i])
	{
		if (!is_ifs_char(src[i], s_ifs) && !is_ifs_char(src[i], d_ifs))
		{
			len = count_not_ifs_len(src, &i, s_ifs, d_ifs);
			(*fields)[idx++] = ft_strsub(src, i - len, len);
			if (src[i] == '\0')
				break ;
			skip_ifs_chars(src, &i, s_ifs, d_ifs);
		}
		while (is_ifs_char(src[i], s_ifs))
			i++;
		while (is_ifs_char(src[i], d_ifs) && ++i)
			(*fields)[idx++] = ft_strnew(0);
	}
	(*fields)[idx] = NULL;
}

char			**field_splitting(const char *source)
{
	char		**fields;
	char		*ifs;
	char		*s_ifs;
	char		*d_ifs;

	if (!source || *source == '\0')
		return (NULL);
	ifs = ft_getenv(env, "IFS");
	if (ifs == NULL)
		ifs = " \t\n";
	else if (*ifs == '\0')
		return (NULL);
	fill_space_ifs(&s_ifs, ifs);
	fill_delimiters_ifs(&d_ifs, ifs);
	fill_fields(&fields, source, s_ifs, d_ifs);
	ft_strdel(&s_ifs);
	ft_strdel(&d_ifs);
	return (fields);
}

t_word_list		*field_splitting_list(const char *source)
{
	char		**fields;
	int			i;
	t_word_list	*list;
	t_word_list	*tmp;

	fields = field_splitting(source);
	if (fields == NULL)
		return (NULL);
	if (fields && !fields[0])
	{
		del_array(fields);
		return (NULL);
	}
	i = 0;
	list = create_word_node(fields[0]);
	list->need_quote_rm = 0;
	tmp = list;
	while (fields[++i] != NULL)
	{
		tmp->next = create_word_node(fields[i]);
		tmp->need_quote_rm = 0;
		tmp = tmp->next;
	}
	del_array(fields);
	return (list);
}
