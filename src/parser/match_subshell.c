#include "parser.h"

t_subshell *init_subshell()
{
    t_subshell *fresh;

    fresh = (t_subshell*)ft_memalloc(sizeof(t_subshell));
    if (!fresh)
        return (NULL);
    return (fresh);
}

// TODO Используется помимо этой функции еще в
// TODO match_brace_group, match_and_or, match_pipeline следует вынести в
// TODO отдельный файл
void    clean_grammar_linebreaks(t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;

    tokbuf_l = NULL;
    while  (gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
        erase_tokbuf(&tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
}

/*
** subshell использует '(' и ')'
*/

int     match_subshell(t_subshell **subshell, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;
    t_tokens tk_type;

    tokbuf_l = NULL;
    *subshell = init_subshell();
    gett(g_parser_input_string, tokbuf_g, &tokbuf_l); // Здесь должен быть токен '(', просто вытаскиваем его. Ожидаем потому что есть проверка в match_command
    if (match_compound_list(&(*subshell)->compound_list, tokbuf_g) != PARSER_SUCCES)
        return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    if  (gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type != RBRACKET)
        return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    tk_type = gett(g_parser_input_string, tokbuf_g, &tokbuf_l)->tk_type;
    ungett(tokbuf_g, &tokbuf_l);
    if (is_redirect(tk_type) || tk_type == IO_NUMBER)
    {
        if (match_io_redirect(&(*subshell)->redirects, tokbuf_g) != PARSER_SUCCES)
            return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
    }
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}
