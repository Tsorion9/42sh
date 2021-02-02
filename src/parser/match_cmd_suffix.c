#include "parser.h"

int     match_cmd_arg(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    add_word_to_list(&(*simple_cmd)->words, token);
    if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
        return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}

/*
** if token type is TOKEN_END, then EOF reached in noninteractive mode
** Set token type TOKEN_CTRL_C just to skip printing error message
*/

int 	check_token_end(t_token *token, t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	if (token->tk_type == TOKEN_END && !g_parser_input_string)
	{
		token->tk_type = TOKEN_CTRL_C;
		return (return_err_and_flush_tokens(tokbuf_g, tokbuf_l));
	}
	return (PARSER_SUCCES);
}

int     match_cmd_suffix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == IO_NUMBER || is_redirect(token->tk_type))
    {
        if (match_io_redirect(&(*simple_cmd)->redirects, tokbuf_g) !=
        														PARSER_SUCCES)
            return (PARSER_FAIL);
		if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
    }
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == WORD)
    {
        if (match_cmd_arg(simple_cmd, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
    }
    return (check_token_end(token, tokbuf_g, &tokbuf_l));
}
