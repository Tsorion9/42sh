/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:42:16 by jsance            #+#    #+#             */
/*   Updated: 2021/02/24 00:38:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "t_hashalias.h"

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

void			substitute_alias(t_token *token, t_deque **tokbuf_g)
{
	char		*value;
	char		*key;
	t_deque		*tokbuf;
	t_deque		*queue;
	int			i;

	i = 0;
	tokbuf = NULL;
	if (token->tk_type == WORD && !token->do_not_expand_alias)
	{
		value = search_alias_1(token->value);
		// ft_printf("value: %s\n", value);
		if (value)
		{
			key = ft_strdup(token->value);
			if ((tokbuf = check_tokbuf(key, value)))
			{
				while (ft_strcmp(key, value) && (tokbuf = check_tokbuf(key, value)))
				{
					// ft_printf("value: %s\n", value);
					// gett(g_parser_input_str, tokbuf_g, &tokbuf);
					// erase_tokbuf(&tokbuf);
					// tokbuf = deque_copy(search_tokbuf(key));
					// write(1, "2", 1);
					// if (tokbuf == NULL)
					// 	return ;
					
					// if (i)
					// {
						t_token *del = pop_front(*tokbuf_g);
						free(del->value);
						free(del);
					// }
					t_deque *copy = deque_copy(tokbuf);
					value = ft_strdup(copy->first->token->value);
					deque_apply_inplace(copy, &set_do_not_expand);
					flush_tokbuf(tokbuf_g, &copy);
					i++;
				}
			}
			else if (!tokbuf)
			{
				tokbuf = deque_copy(search_tokbuf(key));
				deque_apply_inplace(tokbuf, &set_do_not_expand);
				t_token *del = pop_front(*tokbuf_g);
				free(del->value);
				free(del);
				flush_tokbuf(tokbuf_g, &tokbuf);
			}
			free(key);
			free(value);
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
