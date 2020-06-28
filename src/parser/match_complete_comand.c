/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_complete_comand.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	match_complete_command(t_deque **command, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;

	tokbuf_l = NULL;
	if (match_list(command, tokbuf_g) == PARSER_FAILURE)
	{
		syntax_error(((t_token *)((*tokbuf_g)->last->data)));
		erase_tokbuf(&tokbuf_l);
		return (PARSER_FAILURE);
	}
	if (gett(tokbuf_g, &tokbuf_l)->token_type != sep)
		ungett(tokbuf_g, &tokbuf_l);
	if (gett(tokbuf_g, &tokbuf_l)->token_type != __newline)
	{
		ungett(tokbuf_g, &tokbuf_l);
		erase_tokbuf(&tokbuf_l);
		syntax_error(((t_token *)((*tokbuf_g)->last->data)));
		return (PARSER_FAILURE);
	}
	erase_tokbuf(&tokbuf_l);
	return (check_parser_signals());
}
