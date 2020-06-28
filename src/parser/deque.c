/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:24 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"
#include "t2list.h"

/*
** In-place insertion
*/

void			*push_front(t_deque **d, void *new)
{
	if (!*d)
	{
		*d = xmalloc(sizeof(t_deque));
		if (!*d)
			return (NULL);
		(*d)->first = NULL;
		(*d)->last = NULL;
	}
	if (!lst2_add(&(*d)->first, new))
		return (NULL);
	if (!(*d)->last)
		(*d)->last = (*d)->first;
	return (*d);
}

void			*push_back(t_deque **d, void *new)
{
	t_2list	*lst;

	if (!*d)
	{
		*d = xmalloc(sizeof(t_deque));
		if (!*d)
			return (NULL);
		(*d)->first = NULL;
		(*d)->last = NULL;
	}
	if (!(lst = lst2_new(new)))
		return (NULL);
	if (!(*d)->last)
	{
		(*d)->first = lst;
		(*d)->last = (*d)->first;
		return (*d);
	}
	(*d)->last->next = lst;
	lst->prev = (*d)->last;
	(*d)->last = lst;
	return (*d);
}

/*
** List element is erased, but not data!
*/

void			*pop_back(t_deque *d)
{
	t_2list	*l;
	void	*data;

	if (!d)
		return (NULL);
	l = d->last;
	if (d->last)
	{
		data = l->data;
		d->last = d->last->prev;
		free(l);
		if (d->last)
			d->last->next = NULL;
		else
			d->first = NULL;
	}
	else
		return (NULL);
	return (data);
}

void			*pop_front(t_deque *d)
{
	t_2list	*l;
	void	*data;

	if (!d || !d->first)
		return (NULL);
	l = d->first;
	data = l->data;
	d->first = d->first->next;
	free(l);
	if (d->first)
		d->first->prev = NULL;
	else
		d->last = NULL;
	return (data);
}

void			deque_del(t_deque **d, void (*del)(void *))
{
	if (!d || !*d)
		return ;
	lst2del(&((*d)->first), del);
	free(*d);
	*d = NULL;
}
