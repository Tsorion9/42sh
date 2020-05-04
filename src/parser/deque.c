#include "deque.h"
#include "t2list.h"

/*
** In-place insertion
*/

void			*push_front(t_deque **d, void *new)
{
	if (!*d)
	{
		*d = malloc(sizeof(t_deque));
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
		*d = malloc(sizeof(t_deque));
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
	if (d->last)	 /* Deque is nonempty */
	{
		data = l->data;
		d->last = d->last->prev;
		free(l);
		if (d->last) /* Deque containned >1 elements */
			d->last->next = NULL;
		else		 /* Deque containned ==1 element. We removed it */
			d->first = NULL;
	}
	else
		return (NULL); /* Deque was empty */
	return (data);
}

void			*pop_front(t_deque *d)
{
	t_2list	*l;
	void	*data;

	if (!d || !d->first)		/* Deque was empty or did not exist */
		return (NULL);
	l = d->first;
	data = l->data;
	d->first = d->first->next;
	free(l);
	if (d->first)				/* Deque containned >1 elements */
		d->first->prev = NULL;
	else						/* Deque containned ==1 element. */
		d->last = NULL;
	return (data);
}

/*
** Return the n-th element from start
*/

void			*deque_n_th(t_deque *deque, int n)
{
	t_2list *tmp;

	if (!deque)
		return (NULL);
	tmp = deque->first;
	while (n--)
	{
		if (tmp->next)
			tmp = tmp->next;
		else 
			return (NULL);
	}
	return (tmp->data);
}

void			deque_del(t_deque **d, void (*del)(void *))
{
	if (!d || !*d)
		return ;
	lst2del(&((*d)->first), del);
	free(*d);
	*d = NULL;
}