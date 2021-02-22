/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokbuf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/10/26 19:45:55 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "lexer.h"

/*
** Put the token from gloabl queue to local queue
** return it's value
*/

t_token		*gett(char **s, t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	t_token	*next;
	t_token	*fresh;
	char	*save_s;

	if (!tokbuf_g || !*tokbuf_g || !(*tokbuf_g)->first)
	{
		save_s = NULL;
		if (s)
			save_s = *s;
		next = lexer(s);
		if (s && save_s && !*s)
		{
			fresh = malloc(sizeof(t_token));
			fresh->value = NULL;
			fresh->tk_type = TOKEN_END;
			push_back(tokbuf_l, next);
			push_front(tokbuf_g, fresh);
			return (next);
		}
	}
	else
		next = pop_front(*tokbuf_g);
	push_back(tokbuf_l, next);
	return (next);
}

/*
** Put the last read token back into the global buffer
*/

void		ungett(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	t_token	*last;

	last = pop_back(*tokbuf_l);
	if (!last)
	{
		free(*tokbuf_l);
		return ;
	}
	push_front(tokbuf_g, last);
	if (deque_len(*tokbuf_l) == 0)
	{
		free(*tokbuf_l);
		*tokbuf_l = 0;
	}
}

void		del_token(t_token *token)
{
	free(token->value);
	free(token);
}

void		erase_tokbuf(t_deque **tokbuf)
{
	deque_del(tokbuf, del_token);
}

/*
** Put unknown quantity of tokens back to the global buffer
** TODO: We should do it in constant time
*/

void		flush_tokbuf(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	while (*tokbuf_l && (*tokbuf_l)->first)
		ungett(tokbuf_g, tokbuf_l);
}
