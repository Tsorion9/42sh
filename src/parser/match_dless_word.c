/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_dless_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:21:55 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:21:56 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "heredoc.h"

int		match_dless_word(t_redirect **redirect, t_deque **tokbuf_g)
{
	t_deque *tokbuf_l;
	t_token *token;

	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (token->tk_type != DLESS)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (PARSER_FAIL);
	}
	set_instruction(redirect, token->tk_type);
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (token->tk_type != WORD)
		return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
	if (contain_quote(token->value))
		(*redirect)->need_expand_heredoc = 0;
	else
		(*redirect)->need_expand_heredoc = NEED_EXPAND_HERE;
	heredoc_action(ADD_DELIMITER, token->value, &(*redirect)->heredoc_value,
				NULL);
	(*redirect)->redirector->filename = ft_strdup(token->value);
	erase_tokbuf(&tokbuf_l);
	return (PARSER_SUCCES);
}
