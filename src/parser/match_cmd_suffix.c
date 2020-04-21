#include "parser.h"

static void	save_string(t_simple_cmd **cmd, t_deque *tokbuf_l)
{
	t_token	*tok;

	tok = pop_front(tokbuf_l);
	push_back(&((*cmd)->wl), tok->attribute); 
	free(tok);
}

int	match_cmd_suffix(t_simple_cmd **cmd, t_deque **tokbubf_g)
{
	t_deque	*tokbuf_l;
	int		success;
	int		any_success;

	tokbuf_l = NULL;
	any_success = -1;
	success = 1;
	while (success)
	{
		any_success += success;
		if (gett(tokbubf_g, &tokbuf_l)->token_type != word)
		{
			ungett(tokbubf_g, &tokbuf_l);
			success = 0;
		}
		else
			save_string(cmd, tokbuf_l);
		if (match_io_redirect(*cmd, tokbubf_g) == PARSER_FAILURE && !success)
			break ;
		success = 1;
	}
	return (any_success > 0 ? PARSER_SUCCESS : PARSER_FAILURE);
}
