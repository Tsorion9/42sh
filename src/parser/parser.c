#include "parser.h"

/*
** TODO: heredocs. xmalloc
*/

t_deque	*parser()
{
	t_deque			*command;
	static t_deque	*tokbuf_g;
	t_deque			*tokbuf_l;

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
			exit (-1);
		syntax_error_state_action(SYNTAX_ERROR_STATE_SET, SYNTAX_ERROR_STATE_NOT_OK);
		return (NULL);
	}
	gather_heredocs();
	return (command);
}
