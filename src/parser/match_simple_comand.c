#include "parser.h"

static void	enter(t_simple_cmd **cmd, t_deque **tokbuf_l)
{
	*cmd = malloc(sizeof(t_simple_cmd));
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
				int status
				)
{
	if (status == PARSER_SUCCESS)
	{
		erase_tokbuf(tokbuf_l);
		return (PARSER_SUCCESS);
	}
	else
	{
		flush_tokbuf(tokbuf_g, tokbuf_l);
		rm_simple_cmd(*cmd);
		return (PARSER_FAILURE);
	}
}

int	match_simple_command(t_simple_cmd **cmd, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;
	int		prefix_matched;
	t_token	*tok;

	enter(cmd, &tokbuf_l);
	if ((prefix_matched = match_cmd_prefix(cmd, tokbuf_g)) == PARSER_FAILURE)
	{
		/* Cleanup the side-effects of match_cmd_prefix() */
		exit_(cmd, &tokbuf_l, tokbuf_g, PARSER_FAILURE); 
		enter(cmd, &tokbuf_l);
	}
	if (gett(tokbuf_g, &tokbuf_l)->token_type != word)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (exit_(cmd, &tokbuf_l, tokbuf_g,\
					(prefix_matched == PARSER_FAILURE) ?\
					PARSER_FAILURE : PARSER_SUCCESS));
	}
	tok = pop_front(tokbuf_l);
	push_back(&((*cmd)->wl), tok->attribute); //First word to wordlist
	free(tok);
	match_cmd_suffix(cmd, tokbuf_g);
	return (exit_(cmd, &tokbuf_l, tokbuf_g, PARSER_SUCCESS));
}
