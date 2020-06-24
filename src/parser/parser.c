/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 22:58:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "inc21sh.h"

t_deque	*parser(void)
{
	t_deque			*command;
	static t_deque	*tokbuf_g;
	t_deque			*tokbuf_l;

	if (gett(&tokbuf_g, &tokbuf_l)->token_type == eof)
		reset_exit(0);
	ungett(&tokbuf_g, &tokbuf_l);
	command = NULL;
	tokbuf_l = NULL;
	while (gett(&tokbuf_g, &tokbuf_l)->token_type == __newline)
		erase_tokbuf(&tokbuf_l);
	ungett(&tokbuf_g, &tokbuf_l);
	if (PARSER_FAILURE == match_complete_command(&command, &tokbuf_g))
	{
		rm_compl_cmd(&command);
		erase_tokbuf(&tokbuf_g);
		if (!isatty(0))
			exit(-1);
		syntax_error_state_action(SYNTAX_ERROR_STATE_SET,\
				SYNTAX_ERROR_STATE_NOT_OK);
		return (NULL);
	}
	gather_heredocs();
	return (command);
}
