#include "parser.h"
#include "t_hashalias.h"

t_simple_cmd *init_simple_cmd()
{
    t_simple_cmd *fresh;

    fresh = (t_simple_cmd*)ft_memalloc(sizeof(t_simple_cmd));
    return (fresh);
}
// Используется не только в этой функции лучше вынести в отдельный файл
int		is_redirect(t_tokens type)
{
    if (type == DLESS || type == DGREAT || type == LESS ||
        type == GREAT || type == LESSAND || type == GREATAND)
        return (1);
    return (0);
}

int     error_cln_simple_command(t_simple_cmd **simple_cmd)
{
    t_word_list *tmp;
    t_word_list *del;

    if ((*simple_cmd)->words)
    {
        tmp = (*simple_cmd)->words;
        while (tmp)
        {
            free(tmp->word);
            del = tmp;
            tmp = tmp->next;
            free(del);
        }
    }
    free(*simple_cmd);
    *simple_cmd = NULL;
    return (PARSER_ERROR);
}

void 	set_do_not_expand(t_token **token)
{
	(*token)->do_not_expand_alias = 1;
}

void	substitute_alias(t_token *token, t_deque **tokbuf_g)
{
	char	*value;
	char 	*key;
	t_deque	*tokbuf;

	tokbuf = NULL;
	if (token->tk_type == WORD && !token->do_not_expand_alias)
	{
		value = search_alias(token->value);
		if (value)
		{
			key = ft_strdup(token->value);
		 gett(g_parser_input_string, tokbuf_g, &tokbuf);
			erase_tokbuf(&tokbuf);
			tokbuf = deque_copy(search_tokbuf(key));
			deque_apply_inplace(tokbuf, &set_do_not_expand);
			flush_tokbuf(tokbuf_g, &tokbuf);
			free(key);
		}
	}
}

int     match_simple_command(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
    t_deque *tokbuf_l;

    tokbuf_l = NULL;
    *simple_cmd = init_simple_cmd();
    t_token *token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
    ungett(tokbuf_g, &tokbuf_l);
    substitute_alias(token, tokbuf_g);
    token = gett(g_parser_input_string, tokbuf_g, &tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
    if (token->tk_type == WORD || token->tk_type == IO_NUMBER
        || is_redirect(token->tk_type))
    {
        if (match_cmd_prefix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
        if (match_cmd_word(&(*simple_cmd)->words, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
        if (match_cmd_suffix(simple_cmd, tokbuf_g) != PARSER_SUCCES)
            return (PARSER_ERROR);
        return (PARSER_SUCCES);
    }
    return (PARSER_ERROR);
}
