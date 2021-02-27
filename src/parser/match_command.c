/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:14:52 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:14:53 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_command	*init_command(void)
{
	t_command	*fresh;

	fresh = (t_command*)ft_memalloc(sizeof(t_command));
	if (!fresh)
		return (NULL);
	return (fresh);
}

/*
** LBRACE = '{'
** LBRACKET = '('
*/

void		set_command_type(t_command **command, t_deque **tokbuf_g,
								t_deque **tokbuf_l)
{
	t_token	*token;

	token = gett(g_parser_input_str, tokbuf_g, tokbuf_l);
	if (token->tk_type == LBRACKET)
		(*command)->cmd_type = SUBSHELL;
	else if (token->tk_type == LBRACE)
		(*command)->cmd_type = BRACE_GROUP;
	else
		(*command)->cmd_type = SIMPLE_CMD;
	ungett(tokbuf_g, tokbuf_l);
}

/*
** "(" и ")" лексер всегда разделяет как токен
** "{" и "}" либо токены, либо слово
** if token value = "(" -> subshell
** if token value = "{" -> brace group
** else simple command
*/

int			match_command(t_command **command, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;

	tokbuf_l = NULL;
	*command = init_command();
	set_command_type(command, tokbuf_g, &tokbuf_l);
	if ((*command)->cmd_type == SUBSHELL)
	{
		return (PARSER_ERROR);
		if (match_subshell(&(*command)->subshell, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
	}
	else if ((*command)->cmd_type == BRACE_GROUP)
	{
		return (PARSER_ERROR);
		if (match_brace_group(&(*command)->brace_group, tokbuf_g) != 1)
			return (PARSER_ERROR);
	}
	else if (match_simple_command(&(*command)->simple_cmd, tokbuf_g) != 1)
		return (PARSER_ERROR);
	return (PARSER_SUCCES);
}
