/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:26 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	enter(t_deque **tokbuf_l, t_pipeline **pipeline)
{
	*tokbuf_l = NULL;
	*pipeline = xmalloc(sizeof(t_pipeline));
	if (*pipeline)
	{
		(*pipeline)->bang = 0;
		(*pipeline)->commands = NULL;
	}
}

int			match_pipeline(t_deque **command, t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_pipeline	*pipeline;
	int			exit_status;

	enter(&tokbuf_l, &pipeline);
	if (gett(tokbuf_g, &tokbuf_l)->token_type != bang)
		ungett(tokbuf_g, &tokbuf_l);
	else
		pipeline->bang = 1;
	exit_status = match_pipe_sequence(pipeline, tokbuf_g);
	if (exit_status == PARSER_FAILURE)
	{
		if (pipeline->bang)
			ungett(tokbuf_g, &tokbuf_l);
		free(pipeline);
		return (PARSER_FAILURE);
	}
	push_back(command, pipeline);
	return (check_parser_signals());
}
