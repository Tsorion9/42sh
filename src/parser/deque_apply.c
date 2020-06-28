/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:24 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

void	deque_apply(t_deque *d, void (*f)(void *))
{
	if (!d)
		return ;
	lst2_apply(d->first, f);
}

void	deque_apply_inplace(t_deque *d, void (*f)(void **))
{
	if (!d)
		return ;
	lst2_apply_inplace(d->first, f);
}
