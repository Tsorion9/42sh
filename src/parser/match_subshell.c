#include "parser.h"

t_subshell *init_subshell()
{
    t_subshell *fresh;

    fresh = (t_subshell*)ft_memalloc(sizeof(t_subshell));
    if (!fresh)
        return (NULL);
    return (fresh);
}

// Используется помимо этой функции еще в
// match_brace_group, match_and_or, match_pipeline следует вынести в отдельный файл
void    clean_grammar_linebreaks(t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;

    tokbuf_l = NULL;
    while (gett(tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
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
    gett(tokbuf_g, &tokbuf_l); // Здесь должен быть токен '(', просто вытаскиваем его. Ожидаем потому что есть проверка в match_command
    if (match_compound_list(&(*subshell)->compound_list, tokbuf_g) != PARSER_SUCCES)
        return (PARSER_ERROR);
    if (gett(tokbuf_g, &tokbuf_l)->tk_type != RBRACKET)
        return (PARSER_ERROR);
    tk_type = gett(tokbuf_g, &tokbuf_l)->tk_type;
    ungett(tokbuf_g, &tokbuf_l);
    if (tk_type != NEWLINE)
    {
        if (match_io_redirect(&(*subshell)->redirects, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
    }
    erase_tokbuf(&tokbuf_l);
    return (PARSER_SUCCES);
}