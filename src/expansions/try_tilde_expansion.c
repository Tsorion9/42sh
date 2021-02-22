/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try_tilde_expansion.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:24:17 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:27:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/*
** На вход ожидает получить строку с кавычкой в первом символе
** Пример:	'someword'more
** 			"someword"more
** Возвращает индекс закрывающей кавычки
*/
// TODO Возможно стоит вынести в либу
size_t		find_closing_quote(char *data)
{
	char	quote;
	size_t	i;
	size_t	len;

	quote = data[0];
	if (quote != '\'' && quote != '"')
		return (0);
	len = strlen(data);
	i = 0;
	while (++i < len)
	{
		if (data[i] == quote)
		{
			if (data[i - 1] == '\\')
			{
				if (quote != '\'')
					continue;
			}
			return (i);
		}
	}
	return (0);
}

static void	tilde_set_quote_state(const char *s, int *quoted_state, size_t *j)
{
	*j = 0;
	*quoted_state = 0;
	while (s[*j] != '\0' && *quoted_state == 0)
	{
		if (s[*j] == '\\')
		{
			*quoted_state = 1;
			(*j)++;
		}
		else if (s[*j] == '\'' || s[*j] == '"')
		{
			*quoted_state = 1;
			*j += find_closing_quote((char*)s + *j);
		}
		else if (s[*j] == '/')
			break ;
		(*j)++;
	}
}

void		try_tilde_expansion(char **src_word, size_t *i, int word_state,
							int inside_assignment_word)
{
	size_t	j;
	int		quoted_state;

	if ((word_state & IN_DQUOTE_STATE) || (word_state & IN_QUOTE_STATE))
	{
		(*i)++;
		return ;
	}
	if (*i == 0 || (inside_assignment_word &&
				(((*src_word)[*i - 1] == '=') || (*src_word)[*i - 1] == ':')))
	{
		tilde_set_quote_state(*src_word, &quoted_state, &j);
		if (quoted_state)
		{
			*i = j;
			return ;
		}
		tilde_expansion(src_word, i, inside_assignment_word);
	}
	else if ((*src_word)[*i] == '/' || *i)
		(*i)++;
}
