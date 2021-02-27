/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_alias_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 00:18:19 by nriker            #+#    #+#             */
/*   Updated: 2021/02/27 00:25:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void			check_tail(t_deque *tail, t_deque **tokbuf_g)
{
	t_token *tail_token;

	while (tail && tail->first && tail->last)
	{
		tail_token = pop_front(tail);
		push_back(tokbuf_g, tail_token);
	}
	erase_tokbuf(&tail);
}

void			table_is_not_null(char *key, char **value, t_deque **tokbuf_g)
{
	t_deque		*tail;
	t_hashtable	*table;
	t_deque		*tokbuf;
	t_deque		*copy;

	table = NULL;
	tail = deque_copy(search_tokbuf(key));
	delete_first_token(&tail);
	while (ft_strcmp(key, *value) && (table = check_tokbuf(key, *value))
			&& !table->meet_alias)
	{
		tokbuf = table->tokbuf_value;
		table->meet_alias = 1;
		delete_first_token(tokbuf_g);
		copy = deque_copy(tokbuf);
		ft_strdel(value);
		*value = ft_strdup(copy->first->token->value);
		deque_apply_inplace(copy, &set_do_not_expand);
		flush_tokbuf(tokbuf_g, &copy);
	}
	check_tail(tail, tokbuf_g);
}

void			table_is_null(char *key, t_deque **tokbuf_g)
{
	t_deque		*tokbuf;

	tokbuf = deque_copy(search_tokbuf(key));
	deque_apply_inplace(tokbuf, &set_do_not_expand);
	delete_first_token(tokbuf_g);
	flush_tokbuf(tokbuf_g, &tokbuf);
}

void			value_of_token_is_null(t_token *token, t_deque **tokbuf_g)
{
	t_deque		*tokbuf;

	tokbuf = deque_copy(search_tokbuf(token->value));
	if (tokbuf)
	{
		delete_first_token(tokbuf_g);
		deque_apply_inplace(tokbuf, &set_do_not_expand);
		flush_tokbuf(tokbuf_g, &tokbuf);
	}
}

void			value_of_token_is_not_null(t_token *token, t_deque **tokbuf_g)
{
	char		*key;
	char		*value;
	t_hashtable	*table;

	value = search_alias_1(token->value);
	key = ft_strdup(token->value);
	if ((table = check_tokbuf(key, value)))
	{
		table_is_not_null(key, &value, tokbuf_g);
	}
	else if (!table)
		table_is_null(key, tokbuf_g);
	free(key);
	free(value);
}
