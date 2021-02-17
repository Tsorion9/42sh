/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:07:33 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:07:34 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_subshell	*init_subshell(void)
{
	t_subshell	*fresh;

	fresh = (t_subshell*)ft_memalloc(sizeof(t_subshell));
	if (!fresh)
		return (NULL);
	return (fresh);
}

/*
** subshell использует '(' и ')'
*/

int			match_subshell(t_subshell **subshell, t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_tokens	tk_type;

	tokbuf_l = NULL;
	*subshell = init_subshell();
	gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (match_compound_list(&(*subshell)->compound_list, tokbuf_g) != 1)
		return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
	if (gett(g_parser_input_str, tokbuf_g, &tokbuf_l)->tk_type != RBRACKET)
		return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
	tk_type = gett(g_parser_input_str, tokbuf_g, &tokbuf_l)->tk_type;
	ungett(tokbuf_g, &tokbuf_l);
	if (is_redirect(tk_type) || tk_type == IO_NUMBER)
	{
		if (match_io_redirect(&(*subshell)->redirects, tokbuf_g) != 1)
			return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
	}
	erase_tokbuf(&tokbuf_l);
	return (PARSER_SUCCES);
}
