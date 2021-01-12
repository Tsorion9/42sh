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

t_token	*gett(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	t_token	*next;

	if (!tokbuf_g || !*tokbuf_g || !(*tokbuf_g)->first)
		next = lexer();
	else
		next = pop_front(*tokbuf_g);
	push_back(tokbuf_l, next);
	return (next);
}

/*
** Put the last read token back into the global buffer
*/

void	ungett(t_deque **tokbuf_g, t_deque **tokbuf_l)
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

void	del_token(t_token *token)
{
	free(token->value);
	free(token);
}

void	erase_tokbuf(t_deque **tokbuf)
{
	deque_del(tokbuf, del_token);
}

/*
** Put unknown quantity of tokens back to the global buffer
** TODO: We should do it in constant time
*/

void	flush_tokbuf(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	while (*tokbuf_l && (*tokbuf_l)->first)
		ungett(tokbuf_g, tokbuf_l);
}
