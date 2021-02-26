/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:42:16 by jsance            #+#    #+#             */
/*   Updated: 2021/02/26 21:42:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "t_hashalias.h"

int g_alias;

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd *fresh;

	fresh = (t_simple_cmd*)ft_memalloc(sizeof(t_simple_cmd));
	return (fresh);
}

void			set_do_not_expand(t_token **token)
{
	(*token)->do_not_expand_alias = 1;
}

void			set_null_meet_alias(void)
{
	t_hashalias		*alias;
	t_hashtable		*table;
	int				i;

	i = 0;
	if ((alias = static_hashalias_action(get)) == NULL
		|| alias->hd == NULL)
		return ;
	while (i < HASH_SIZE)
	{
		table = alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				table->meet_alias = 0;
				table = table->next;
			}
		}
		i++;
	}
}

void			substitute_alias(t_token *token, t_deque **tokbuf_g)
{
	char		*value;
	char		*key;
	t_deque		*tokbuf;
	t_deque		*tail;
	t_hashdata	*check_table;
	t_hashtable	*table;
	int			i;

	i = 0;
	tokbuf = NULL;
	if (token->tk_type == WORD && !token->do_not_expand_alias)
	{
		value = search_alias_1(token->value);
		if (value == NULL)
		{
			tokbuf = deque_copy(search_tokbuf(token->value));
			if (tokbuf)
			{
				t_token *del = pop_front(*tokbuf_g);
				free(del->value);
				free(del);
				deque_apply_inplace(tokbuf, &set_do_not_expand);
				flush_tokbuf(tokbuf_g, &tokbuf);
				g_alias = 1;
			}
		}
		if (value)
		{
			key = ft_strdup(token->value);
			if ((table = check_tokbuf(key, value)))
			{
				tail = deque_copy(search_tokbuf(token->value));
				t_token *del = pop_front(tail);
				free(del->value);
				free(del);
				while (ft_strcmp(key, value) && (table = check_tokbuf(key, value))
						&& !table->meet_alias)
				{
					tokbuf = table->tokbuf_value;
					table->meet_alias = 1;
					t_token *del = pop_front(*tokbuf_g);
					free(del->value);
					free(del);
					t_deque *copy = deque_copy(tokbuf);
					ft_strdel(&value);
					value = ft_strdup(copy->first->token->value);
					deque_apply_inplace(copy, &set_do_not_expand);
					flush_tokbuf(tokbuf_g, &copy);
					i++;
				}
				while (tail && tail->first && tail->last)
				{
					t_token *tail_token = pop_front(tail);
					push_back(tokbuf_g, tail_token);
				}
				erase_tokbuf(&tail);
				g_alias = 1;
			}
			else if (!table)
			{
				tokbuf = deque_copy(search_tokbuf(key));
				deque_apply_inplace(tokbuf, &set_do_not_expand);
				t_token *del = pop_front(*tokbuf_g);
				free(del->value);
				free(del);
				flush_tokbuf(tokbuf_g, &tokbuf);
				g_alias = 1;
			}
			free(key);
			free(value);
			set_null_meet_alias();
		}
	}
}

static void		check_alias(t_token **token, t_deque **tokbuf_g,
							t_deque **tokbuf_l)
{
	*token = gett(g_parser_input_str, tokbuf_g, tokbuf_l);
	ungett(tokbuf_g, tokbuf_l);
	substitute_alias(*token, tokbuf_g);
	*token = gett(g_parser_input_str, tokbuf_g, tokbuf_l);
	ungett(tokbuf_g, tokbuf_l);
}

int				match_simple_command(t_simple_cmd **simple_cmd,
							t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_token		*token;

	tokbuf_l = NULL;
	*simple_cmd = init_simple_cmd();
	check_alias(&token, tokbuf_g, &tokbuf_l);
	if (g_alias)
		return (PARSER_ERROR);
	if (token->tk_type == WORD || token->tk_type == IO_NUMBER
		|| is_redirect(token->tk_type))
	{
		if (match_cmd_prefix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
		if (match_cmd_word(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
		if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
		return (PARSER_SUCCES);
	}
	return (PARSER_ERROR);
}
