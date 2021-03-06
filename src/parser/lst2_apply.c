/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst2_apply.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	lst2_apply(t_2list *l, void (*f)(t_token *))
{
	while (l)
	{
		f(l->token);
		l = l->next;
	}
}

void	lst2_apply_inplace(t_2list *l, void (*f)(t_token **))
{
	while (l)
	{
		f(&(l->token));
		l = l->next;
	}
}
