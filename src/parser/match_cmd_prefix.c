/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_cmd_prefix.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static	void	init_locals(t_deque **tokbuf_l, int *success, int *any_success)
{
	*tokbuf_l = NULL;
	*any_success = -1;
	*success = 1;
}

int				match_cmd_prefix(t_simple_cmd **cmd, t_deque **tokbubf_g)
{
	t_deque	*tokbuf_l;
	int		success;
	int		any_success;

	init_locals(&tokbuf_l, &success, &any_success);
	while (success)
	{
		any_success += success;
		if (gett(tokbubf_g, &tokbuf_l)->token_type != ass_word)
		{
			ungett(tokbubf_g, &tokbuf_l);
			success = 0;
		}
		else
		{
			add_ar(cmd, pop_front(tokbuf_l), assignment);
			any_success = 1;
		}
		if (match_io_redirect(*cmd, tokbubf_g) == PARSER_FAILURE && !success)
			break ;
		success = 1;
	}
	flush_tokbuf(tokbubf_g, &tokbuf_l);
	return (any_success > 0 ? check_parser_signals() : PARSER_FAILURE);
}
