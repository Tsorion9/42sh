/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_len.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:24 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

int				deque_len(t_deque *d)
{
	int		i;
	t_2list	*current;

	if (!d)
		return (0);
	i = 0;
	current = d->first;
	while (current)
	{
		i += 1;
		current = current->next;
	}
	return (i);
}
