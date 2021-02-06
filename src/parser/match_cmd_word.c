#include "parser.h"

t_word_list *create_word_node(char *word)
{
    t_word_list *fresh;

    fresh = (t_word_list*)ft_memalloc(sizeof(t_word_list));
    if (!fresh)
        return (NULL);
    fresh->word = ft_strdup(word);
    return (fresh);
}
// Используется не только здесь лучше вынести в отдельную функцию
void    add_word_to_list(t_word_list **word_list, t_token *token)
{
    if (*word_list == NULL)
        *word_list = create_word_node(token->value);
    else
        add_word_to_list(&(*word_list)->next, token);
}

int     match_cmd_word(t_word_list **word_list, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l = NULL;
    t_token *token;

    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    if (token->tk_type == WORD)
    {
        add_word_to_list(word_list, token);
        erase_tokbuf(&tokbuf_l);
        return (PARSER_SUCCES);
    }
    ungett(tokbuf_g, &tokbuf_l);
    return (PARSER_ERROR);
}
