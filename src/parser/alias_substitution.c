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
	destroy_token(&token);
	return (fresh);
}

static t_deque	*substitute_token(t_token *token, int *need_expand_next_token)
{
	t_hashtable	*ht;
	t_hashtable	*ht_l;
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
		ht->meet_alias = 1;
		tokbuf_l = deque_copy(ht->tokbuf_value);
		*need_expand_next_token = ht->expand_next_alias;
	}
	else
		return (create_tokbuf_from_token(token));
	while ((token_l = pop_front(tokbuf_l)))
	{
		ht_l = search_alias_hash_element(token_l->value);
		if (need_expand_l && ht_l && !ht_l->meet_alias)
		{
			ht_l->meet_alias = 1;
			save = substitute_token(token_l, &need_expand_l);
			flush_tokbuf_back(&fresh, save);
			free(save);
		}
		else
		{
			push_back(&fresh, token_l);
			flush_tokbuf_back(&fresh, tokbuf_l);
			break ;
		}
	}
	free(tokbuf_l);
	ht->meet_alias = 0;
	destroy_token(&token);
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
		free(sub_res);
		pop_front(tokbuf_l);
		deque_del(&tokbuf_l, del_token);
		tokbuf_l = NULL;
	}
	flush_tokbuf(tokbuf_g, &fresh);
	free(fresh);
	fresh = NULL;
}