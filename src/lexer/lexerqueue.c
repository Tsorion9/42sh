/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexerqueue.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:02:30 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 21:02:31 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	free_quequ_lexer(t_queue **head)
{
	t_queue *tmp;

	tmp = *head;
	while (tmp)
	{
		tmp = tmp->next;
		free(*head);
		*head = tmp;
	}
}

t_queue	*create_new_queue(char brace)
{
	t_queue	*fresh;

	fresh = (t_queue*)ft_memalloc(sizeof(t_queue));
	if (!fresh)
		return (NULL);
	fresh->brace = brace;
	fresh->quoted = 0;
	fresh->next = NULL;
	return (fresh);
}

void	push(t_lexer_state *token, char brace)
{
	t_queue *new_head;

	if (token->brace_buf == NULL)
		token->brace_buf = create_new_queue(brace);
	else
	{
		new_head = create_new_queue(brace);
		new_head->next = token->brace_buf;
		token->brace_buf = new_head;
	}
}

void	pop(t_lexer_state *token, char brace)
{
	t_queue	*to_delete;

	if (token->brace_buf == NULL)
		return ;
	if (brace == token->brace_buf->brace)
	{
		to_delete = token->brace_buf;
		token->brace_buf = token->brace_buf->next;
		free(to_delete);
	}
}
