#include "libft.h"

int	ft_lstlen(t_list *l)
{
	int	i;

	if (!l)
		return (0);
	i = 1;
	while (l->next)
	{
		l = l->next;
		i++;
	}
	return (i);
}
