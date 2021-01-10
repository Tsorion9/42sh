#include "parser.h"
#include "heredoc.h"

int		match_dless_word(t_redirect **redirect, t_deque **tokbuf_g)
{
	t_deque *tokbuf_l;
	t_token *token;

	tokbuf_l = NULL;
	token = gett(tokbuf_g, &tokbuf_l);
	if (token->tk_type != DLESS)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (PARSER_FAIL);
	}
	set_instruction(redirect, token->tk_type);
	token = gett(tokbuf_g, &tokbuf_l);
	if (token->tk_type != WORD)
	{
		flush_tokbuf(tokbuf_g, &tokbuf_l);
		return (PARSER_FAIL);
	}
	heredoc_action(ADD_DELIMITER, token->value, &(*redirect)->heredoc_value);
	(*redirect)->redirector->filename = ft_strdup(token->value);
	erase_tokbuf(&tokbuf_l);
	return (PARSER_SUCCES);
}
