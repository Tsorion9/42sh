#include "deque.h"
#include "t2list.h"

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
