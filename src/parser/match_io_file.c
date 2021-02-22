/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:13:20 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:13:21 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		is_redirect_io_file(t_tokens type)
{
	if (type == DGREAT || type == LESS || type == GREAT
		|| type == LESSAND || type == GREATAND)
		return (1);
	return (0);
}

int		match_io_file(t_redirect **redirect, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;
	t_token	*token;

	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (!is_redirect_io_file(token->tk_type))
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (PARSER_FAIL);
	}
	set_instruction(redirect, token->tk_type);
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (token->tk_type != WORD)
	{
		flush_tokbuf(tokbuf_g, &tokbuf_l);
		return (PARSER_FAIL);
	}
	(*redirect)->redirector->filename = ft_strdup(token->value);
	erase_tokbuf(&tokbuf_l);
	return (PARSER_SUCCES);
}
