#include "parser.h"

/*
** {io_redirect}
*/

int match_cmd_prefix(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_token *token;

    tokbuf_l = NULL;
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == IO_NUMBER || is_redirect(token->tk_type))
    {
        if (match_io_redirect(&(*simple_cmd)->redirects, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
        if (match_cmd_prefix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
    }
    return (PARSER_SUCCES);
}