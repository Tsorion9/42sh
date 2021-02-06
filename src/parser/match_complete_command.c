#include "parser.h"

t_complete_cmd  *init_complete_command()
{
    t_complete_cmd *fresh;

    fresh = (t_complete_cmd*)ft_memalloc(sizeof(t_complete_cmd));
    if (!fresh)
        return (NULL);
    return (fresh);
}

void            set_separator_op(t_complete_cmd **command, t_token *token)
{
    if (token->tk_type == SEMICOL)
        (*command)->separator_op = OP_SEMICOL;
    else if (token->tk_type == BG)
        (*command)->separator_op = OP_BG;
    else
        (*command)->separator_op = OP_NONE;
}

int             match_complete_command(t_complete_cmd **command, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;

    tokbuf_l = NULL;
    *command = init_complete_command();
    if (match_and_or(&(*command)->and_or, tokbuf_g) != PARSER_SUCCES)
        return (PARSER_ERROR);
    set_separator_op(command, gett(g_parser_input_string, tokbuf_g, &tokbuf_l));
    if ((*command)->separator_op != OP_NONE)
    {
        if  (gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
            erase_tokbuf(&tokbuf_l);
        else
        {
            ungett(tokbuf_g, &tokbuf_l);
            if (match_complete_command(&(*command)->next, tokbuf_g) != PARSER_SUCCES)
                return (PARSER_ERROR);
            erase_tokbuf(&tokbuf_l);
        }
    }
    else
        ungett(tokbuf_g, &tokbuf_l);
    return (PARSER_SUCCES);
}
