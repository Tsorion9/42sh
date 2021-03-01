/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_word_into_queue_tokens.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:34:30 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:34:31 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "lexer.h"

static int	consist_only_blanks(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (!ft_isblank(s[i]))
			return (FUNC_FAIL);
		i++;
	}
	return (FUNC_SUCCESS);
}

t_deque		*split_word_into_queue_tokens(char *word)
{
	t_deque	*deque;
	t_token	*token;
	char	*s;

	s = ft_strdup(word);
	deque = NULL;
	while (s != NULL)
	{
		if (consist_only_blanks(s))
		{
			free_lexer_state(&g_token);
			break ;
		}
		token = lexer(&s);
		push_back(&deque, token);
		// deque_del(str, NULL);
	}
	return (deque);
}
