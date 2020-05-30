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

