/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_simple_command.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:42:16 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 16:10:35 by nriker           ###   ########.fr       */
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
	t_deque		*tokbuf_fresh;
	int			k;

	k = 1;
	data = NULL;
	tokbuf_fresh = NULL;
	// while (k)
	// {
		if (token->tk_type == WORD && !token->do_not_expand_alias)
		{
			value = search_alias_1(token->value);
			if (value == NULL)
				value_of_token_is_null(token, &tokbuf_fresh);
			else
			{
				value_of_token_is_not_null(token, &tokbuf_fresh);
				free(value);
				set_null_meet_alias();
			}
		}
		deque_apply(tokbuf_fresh, print_tokbuf);
		flush_tokbuf_back(tokbuf_fresh, tokbuf_g);
		// erase_tokbuf(tokbuf_g);
		*tokbuf_g = tokbuf_fresh;
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
