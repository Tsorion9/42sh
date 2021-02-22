/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_cmd_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:20:09 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:20:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** {io_redirect}
*/

int	match_cmd_prefix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;
	t_token	*token;

	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
	if (token->tk_type == IO_NUMBER || is_redirect(token->tk_type))
	{
		if (match_io_redirect(&(*simple_cmd)->redirects, tokbuf_g)
														!= PARSER_SUCCES)
			return (PARSER_ERROR);
		if (match_cmd_prefix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
	}
	return (PARSER_SUCCES);
}
