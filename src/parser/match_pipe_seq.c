/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pipe_seq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:26 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** We do not know how many tokens are in local buffer after
** Watch out the order of commands in pipeline
*/

static void	match_pipe_seq_d(t_pipeline *pipeline, t_deque **tokbuf_g)
{
	t_simple_cmd	*cmd;
	t_deque			*tokbuf_l;

	tokbuf_l = NULL;
	if (gett(tokbuf_g, &tokbuf_l)->token_type != pipel)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return ;
	}
	match_linebreak(tokbuf_g, &tokbuf_l);
	if (match_simple_command(&cmd, tokbuf_g) == PARSER_SUCCESS)
	{
		erase_tokbuf(&tokbuf_l);
		push_back(&(pipeline->commands), cmd);
		match_pipe_seq_d(pipeline, tokbuf_g);
	}
	else
		flush_tokbuf(tokbuf_g, &tokbuf_l);
}

int			match_pipe_sequence(t_pipeline *pipeline, t_deque **tokbuf_g)
{
	t_simple_cmd	*cmd;

	cmd = NULL;
	if (match_simple_command(&cmd, tokbuf_g) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	push_front(&(pipeline->commands), cmd);
	match_pipe_seq_d(pipeline, tokbuf_g);
	return (check_parser_signals());
}
