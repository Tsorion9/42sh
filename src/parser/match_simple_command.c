/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:42:16 by jsance            #+#    #+#             */
/*   Updated: 2021/03/01 19:54:37 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "t_hashalias.h"
#include "lexer.h"

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd *fresh;

	fresh = (t_simple_cmd*)ft_memalloc(sizeof(t_simple_cmd));
	return (fresh);
}

void			print_token(t_token token)
{
	ft_printf("%s\n", token.value);
	ft_printf("%s\n", get_token_str(token.tk_type));
}

void			print_tokbuf(t_token *token)
{
	print_token(*token);
}

void			substitute_alias(t_token *token, t_deque **tokbuf_g)
{
	char		*value;
	t_hashtable	*data;
	t_deque		*tokbuf_l;
	t_deque		*first_alias_tokbuf;
	t_deque		*tokbuf_fresh;
	int			k;
	t_token		*tmp;
	t_token		*del;

	k = 1;
	data = NULL;
	tokbuf_fresh = NULL;
	first_alias_tokbuf = NULL;
	// while (k)
	// {
		tmp = pop_front(*tokbuf_g);
		if (tmp->tk_type == WORD && !tmp->do_not_expand_alias)
		{
			value = search_alias_1(tmp->value);
			if (value == NULL)
				non_string_alias(tmp, &tokbuf_fresh);
			else
			{
				first_alias_tokbuf = deque_copy(search_tokbuf(tmp->value));
				del = pop_front(first_alias_tokbuf);
				free(del->value);
				free(del);
				value_of_token_is_not_null(tmp, &tokbuf_fresh);
				free(value);
				set_null_meet_alias();
				free(tmp->value);
				free(tmp);
			}
			flush_tokbuf_back(&tokbuf_fresh, first_alias_tokbuf);
			flush_tokbuf_back(&tokbuf_fresh, *tokbuf_g);
			*tokbuf_g = tokbuf_fresh;
		}
		else
			push_front(tokbuf_g, tmp);
//		deque_apply(tokbuf_fresh, print_tokbuf);
	// 	data = search_alias_hash_element(token->value);
	// 	if (!data || !data->expand_next_alias)
	// 		break ;
	// 	tokbuf_l = NULL;
	// 	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	// 	// data = search_alias_hash_element(token->value);
	// 	if (search_alias_hash_element(token->value))
	// 		k = search_alias_hash_element(token->value)->expand_next_alias;
		
	// }
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
