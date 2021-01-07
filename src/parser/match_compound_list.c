#include "parser.h"

t_compound_list *init_compoumnd_list()
{
    t_compound_list *fresh;

    fresh = (t_compound_list*)ft_memalloc(sizeof(t_compound_list));
    if (!fresh)
        return (NULL);
    return (fresh);
}

void    set_separator_compound_list(t_compound_list **compound_list, t_deque **tokbuf_g, t_deque **tokbuf_l)
{
    t_token *token;

    token = gett(tokbuf_g, tokbuf_l);
    if (token->tk_type == SEMICOL)
        (*compound_list)->separator = SEP_SEMICOL;
    else if (token->tk_type == BG)
        (*compound_list)->separator = SEP_BG;
    else if (token->tk_type == NEWLINE)
        (*compound_list)->separator = SEP_NEWLINE;
    else
        (*compound_list)->separator = SEP_NONE;
    if ((*compound_list)->separator != SEP_NONE)
        clean_grammar_linebreaks(tokbuf_g);
    else
        ungett(tokbuf_g, tokbuf_l);
}

int     match_compound_list(t_compound_list **compound_lst, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;

    tokbuf_l = NULL;
    *compound_lst = init_compoumnd_list();
    clean_grammar_linebreaks(tokbuf_g);
    if (match_and_or(&(*compound_lst)->and_or, tokbuf_g) != PARSER_SUCCES)
        return (PARSER_ERROR);
    set_separator_compound_list(compound_lst, tokbuf_g, &tokbuf_l);
    if ((*compound_lst)->separator != SEP_NONE)
    {
        if (match_compound_list(&(*compound_lst)->next, tokbuf_g) != PARSER_SUCCES)
            clean_compound_list(&(*compound_lst)->next);
    }
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}