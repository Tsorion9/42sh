#include "21sh.h"

void	tc_cursor_n_right(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		tc_cursor_right();
		i++;
	}
}
