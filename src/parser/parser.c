#include "parser.h"

/*
** TODO: heredocs. xmalloc
*/

t_deque	*parser()
{
	t_deque			*command;
	static t_deque	*tokbuf_g;

	command = NULL;
	tokbuf_g = NULL;
	if (PARSER_FAILURE == match_complete_command(&command, &tokbuf_g))
	{
		rm_compl_cmd(&command);
		erase_tokbuf(&tokbuf_g);
	}
	return (command);
}
