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

t_simple_cmd	*init_simple_cmd(void)
{
	t_simple_cmd *fresh;

	fresh = (t_simple_cmd*)ft_memalloc(sizeof(t_simple_cmd));
	return (fresh);
}

int				match_simple_command(t_simple_cmd **simple_cmd,
							t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_token		*token;

	tokbuf_l = NULL;
	*simple_cmd = init_simple_cmd();
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
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
