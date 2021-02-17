/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:31:17 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:31:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static t_token	*copy_token(t_token *token)
{
	t_token	*fresh;

	fresh = (t_token*)ft_memalloc(sizeof(token));
	fresh->value = ft_strdup(token->value);
	fresh->do_not_expand_alias = token->do_not_expand_alias;
	fresh->tk_type = token->tk_type;
	return (fresh);
}

t_deque			*deque_copy(t_deque *source)
{
	t_deque	*fresh;
	int		len;
	int		i;

	len = deque_len(source);
	i = 0;
	fresh = NULL;
	while (i < len)
	{
		push_back(&fresh, copy_token(deque_n_th(source, i)));
		i++;
	}
	return (fresh);
}
