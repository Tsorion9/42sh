/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_cmd_suffix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:59:41 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:59:42 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	match_cmd_arg(t_simple_cmd **simple_cmd, t_deque **tokbuf_g,
		t_token **tok)
{
	t_deque	*tokbuf_l;
	t_token	*token;

	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	add_word_to_list(&(*simple_cmd)->words,
					create_word_node_and_save_alias_info(token));
	if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
		return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
	erase_tokbuf(&tokbuf_l);
	*tok = NULL;
	return (PARSER_SUCCES);
}

/*
** if token type is TOKEN_END, then EOF reached in noninteractive mode
** Set token type TOKEN_CTRL_C just to skip printing error message
*/

static int	check_token_end(t_token *token, t_deque **tokbuf_g,
							t_deque **tokbuf_l)
{
	if (token && token->tk_type == TOKEN_END && !g_parser_input_str)
	{
		token->tk_type = TOKEN_CTRL_C;
		return (return_err_and_flush_tokens(tokbuf_g, tokbuf_l));
	}
	return (PARSER_SUCCES);
}

int			match_cmd_suffix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
	t_deque *tokbuf_l;
	t_token *token;

	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
	if (token->tk_type == IO_NUMBER || is_redirect(token->tk_type))
	{
		if (match_io_redirect(&(*simple_cmd)->redirects, tokbuf_g) !=
																PARSER_SUCCES)
			return (PARSER_FAIL);
		if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
	}
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
	if (token->tk_type == WORD)
	{
		if (match_cmd_arg(simple_cmd, tokbuf_g, &token) != PARSER_SUCCES)
			return (PARSER_ERROR);
	}
	return (check_token_end(token, tokbuf_g, &tokbuf_l));
}
