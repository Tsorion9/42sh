/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_simple_comand.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	enter(t_simple_cmd **cmd, t_deque **tokbuf_l)
{
	*cmd = xmalloc(sizeof(t_simple_cmd));
	if (*cmd)
	{
		(*cmd)->wl = NULL;
		(*cmd)->arl = NULL;
	}
	*tokbuf_l = NULL;
}

static int	exit_(
				t_simple_cmd **cmd, \
				t_deque **tokbuf_l,\
				t_deque **tokbuf_g,
				int status)
{
	if (status == PARSER_SUCCESS)
	{
		erase_tokbuf(tokbuf_l);
		return (check_parser_signals());
	}
	else
	{
		if (fuck_checklist_signal_state(0, 0))
			erase_tokbuf(tokbuf_l);
		flush_tokbuf(tokbuf_g, tokbuf_l);
		rm_simple_cmd(*cmd);
		return (PARSER_FAILURE);
	}
}

int			match_simple_command(t_simple_cmd **cmd, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;
	int		prefix_matched;
	t_token	*tok;

	enter(cmd, &tokbuf_l);
	if ((prefix_matched = match_cmd_prefix(cmd, tokbuf_g)) == PARSER_FAILURE)
	{
		exit_(cmd, &tokbuf_l, tokbuf_g, PARSER_FAILURE);
		enter(cmd, &tokbuf_l);
	}
	if (gett(tokbuf_g, &tokbuf_l)->token_type != word)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (exit_(cmd, &tokbuf_l, tokbuf_g,\
					(prefix_matched == PARSER_FAILURE) ?\
					PARSER_FAILURE : check_parser_signals()));
	}
	tok = pop_front(tokbuf_l);
	push_back(&((*cmd)->wl), tok->attribute);
	free(tok);
	match_cmd_suffix(cmd, tokbuf_g);
	return (exit_(cmd, &tokbuf_l, tokbuf_g, check_parser_signals()));
}
