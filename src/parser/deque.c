/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:24 by anton             #+#    #+#             */
/*   Updated: 2021/02/13 13:52:54 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "deque.h"

/*
** In-place insertion
*/

void			*push_front(t_deque **d, t_token *new)
{
	if (!*d)
	{
		*d = ft_memalloc(sizeof(t_deque));
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

void			*push_back(t_deque **d, t_token *new)
{
	t_2list	*lst;

	if (!*d)
	{
		*d = ft_memalloc(sizeof(t_deque));
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
	free(lst);
	return (*d);
}

/*
** List element is erased, but not token!
*/

t_token 		*pop_back(t_deque *d)
{
	t_2list	*l;
	t_token *data;

	if (!d)
		return (NULL);
	l = d->last;
	if (d->last)
	{
		data = l->token;
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
	data = l->token;
	d->first = d->first->next;
	free(l);
	if (d->first)
		d->first->prev = NULL;
	else
		d->last = NULL;
	return (data);
}

void			deque_del(t_deque **d, void (*del)(t_token *))
{
	if (!d || !*d)
		return ;
	lst2del(&((*d)->first), del);
	free(*d);
	*d = NULL;
}
