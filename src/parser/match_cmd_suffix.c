#include "parser.h"

int     match_cmd_arg(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(tokbuf_g, &tokbuf_l);
    add_word_to_list(&(*simple_cmd)->words, token);
    if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
        return (PARSER_ERROR);
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}

int     match_cmd_suffix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == IO_NUMBER || is_redirect(token->tk_type))
    {
        if (match_io_redirect(&(*simple_cmd)->redirects, tokbuf_g) !=
        														PARSER_SUCCES)
            return (PARSER_FAIL);
		if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
			return (PARSER_ERROR);
    }
    token = gett(tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == WORD)
    {
        if (match_cmd_arg(simple_cmd, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
    }
    return (PARSER_SUCCES);
}