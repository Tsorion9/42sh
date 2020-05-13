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
