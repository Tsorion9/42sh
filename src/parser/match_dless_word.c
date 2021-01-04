#include "parser.h"

int     match_dless_word(t_redirect **redirect, t_deque **tokbuf_g)
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
    // Сохранять адреса структур, которые необходимо заполнить после сборки
    // команды
    (*redirect)->heredoc_del = ft_strdup(token->value);
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}