#include "parser.h"

t_word_list *create_word_node(char *word)
{
    t_word_list *fresh;

    fresh = (t_word_list*)ft_memalloc(sizeof(t_word_list));
    if (!fresh)
        return (NULL);
    fresh->word = ft_strdup(word);
    fresh->need_quote_rm = 1;
    return (fresh);
}
// TODO Используется не только здесь лучше вынести в отдельную функцию
void    add_word_to_list(t_word_list **word_list, t_word_list *word)
{
    if (*word_list == NULL)
        *word_list = word;
    else
        add_word_to_list(&(*word_list)->next, word);
}

/*
** cmd_prefix [WORD [cmd_suffix]?]? | WORD [cmd_suffix]?
** Если префикса нет, то WORD является обязательной лексемой
** Иначе WORD является опциональным
*/

int     match_cmd_word(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque		*tokbuf_l = NULL;
    t_token		*token;
    t_redirect	*redirects;

    redirects = (*simple_cmd)->redirects;
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    if (token->tk_type == WORD)
    {
        add_word_to_list(&(*simple_cmd)->words, create_word_node(token->value));
        erase_tokbuf(&tokbuf_l);
        return (PARSER_SUCCES);
    }
    ungett(tokbuf_g, &tokbuf_l);
    return ((redirects != NULL) ? PARSER_SUCCES : PARSER_ERROR);
}
