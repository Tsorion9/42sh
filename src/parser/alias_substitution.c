#include "parser.h"
#include "deque.h"
#include "t_hashalias.h"

/*
** Create t_deque with single token
*/

static t_deque	*create_tokbuf_from_token(t_token *token)
{
	t_deque	*fresh;
	t_token	*copy;

	fresh = NULL;
	copy = copy_token(token);
	push_front(&fresh, copy);
	return (fresh);
}

static t_deque	*substitute_token(t_token *token, int *need_expand_next_token)
{
	t_hashtable	*ht;
	t_deque		*tokbuf_l;
	t_deque		*save;
	t_deque		*fresh;
	t_token		*token_l;
	int 		need_expand_l;

	*need_expand_next_token = 0;
	need_expand_l = 1;
	fresh = NULL;
	save = NULL;
	ht = search_alias_hash_element(token->value);
	if (ht)
	{
		tokbuf_l = deque_copy(ht->tokbuf_value);
		*need_expand_next_token = ht->expand_next_alias;
	}
	else
		return (create_tokbuf_from_token(token));
	while ((token_l = pop_front(tokbuf_l)))
	{
		if (need_expand_l)
		{
			save = substitute_token(token_l, &need_expand_l);
			flush_tokbuf_back(&fresh, save);
		}
		else
		{
			push_back(&fresh, token_l);
			break ;
		}
	}
	return (fresh);
}

/*
** Принимает глобальную очередь из токенов.
** Проверяет токены из очереди и заменяет по правилам алиасов.
*/

void		alias_substitution(t_deque **tokbuf_g)
{
	t_deque *fresh;
	t_deque	*sub_res;
	t_deque	*tokbuf_l;
	t_token	*token;
	int		need_expand_next_token;

	fresh = NULL;
	tokbuf_l = NULL;
	need_expand_next_token = 1;
	while (need_expand_next_token)
	{
		token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
		sub_res = substitute_token(token, &need_expand_next_token);
		flush_tokbuf_back(&fresh, sub_res);
		erase_tokbuf(&tokbuf_l);
	}
	flush_tokbuf(tokbuf_g, &fresh);
}