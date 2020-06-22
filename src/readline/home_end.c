#include "21sh.h"

void	home_end(long c)
{
	int i;

	i = rp()->len;
	while (i--)
		move_cursor(c == HOME ? LEFT_ARROW : RIGHT_ARROW);
}
