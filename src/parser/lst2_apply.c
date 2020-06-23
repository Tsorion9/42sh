#include "deque.h"

void	lst2_apply(t_2list *l, void (*f)(void *))
{
	while (l)
	{
		f(l->data);
		l = l->next;
	}
}

void	lst2_apply_inplace(t_2list *l, void (*f)(void **))
{
	while (l)
	{
		f(&(l->data));
		l = l->next;
	}
}
