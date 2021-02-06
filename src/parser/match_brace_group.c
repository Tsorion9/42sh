#include "parser.h"

t_brace_group *init_brace_group()
{
    t_brace_group *fresh;

    fresh = (t_brace_group*)ft_memalloc(sizeof(t_brace_group));
    if (!fresh)
        return (NULL);
    return (fresh);
}

/*
** brace_group использует '{' и '}'
*/

int         match_brace_group(t_brace_group **brace_group, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_tokens tk_type;

    tokbuf_l = NULL;
    *brace_group = init_brace_group();
    gett(g_parser_input_string, tokbuf_g, &tokbuf_l); // Здесь должен быть токен '{', просто вытаскиваем его. Ожидаем потому что есть проверка в match_command
    if (match_compound_list(&(*brace_group)->compound_list, tokbuf_g) != PARSER_SUCCES)
        return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    if  (gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type != RBRACE)
        return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    tk_type = gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type;
    ungett(tokbuf_g, &tokbuf_l);
    if (tk_type != NEWLINE)
    {
        if (match_io_redirect(&(*brace_group)->redirects, tokbuf_g) != PARSER_SUCCES)
            return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    }
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}
