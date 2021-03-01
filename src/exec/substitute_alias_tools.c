/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_alias_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 00:18:19 by nriker            #+#    #+#             */
/*   Updated: 2021/02/28 16:08:49 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void			flush_tokbuf_back(t_deque **destination, t_deque *src)
{
	t_token *tail_token;

	while (src && src->first && src->last)
	{
		tail_token = pop_front(src);
		push_back(destination, tail_token);
	}
	erase_tokbuf(&src);
}

void			table_is_not_null(char *key, char **value, t_deque **tokbuf_g)
{
	t_hashtable	*table;
	t_deque		*tokbuf;
	t_deque		*copy;

	table = NULL;
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
}

void			table_is_null(char *key, t_deque **tokbuf_g)
{
	t_deque		*tokbuf;

	tokbuf = deque_copy(search_tokbuf(key));
	deque_apply_inplace(tokbuf, &set_do_not_expand);
	// delete_first_token(tokbuf_g);
	flush_tokbuf_back(tokbuf_g, tokbuf);
}

void			non_string_alias(t_token *token, t_deque **tokbuf_fresh)
{
	t_deque		*tokbuf;

	tokbuf = deque_copy(search_tokbuf(token->value));
	if (tokbuf)
	{
		// delete_first_token(tokbuf_fresh);
		deque_apply_inplace(tokbuf, &set_do_not_expand);
		flush_tokbuf_back(tokbuf_fresh, tokbuf);
		free(token->value);
		free(token);
	}
	else
		push_back(tokbuf_fresh, token);
}

void			value_of_token_is_not_null(t_token *token, t_deque **tokbuf_g)
{
	char		*key;
	char		*value;
	t_hashtable	*table;
	int			j;

	value = search_alias_1(token->value, &j);
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

//если alias a=
//a
//то валидно ли выводить execution error?
