#include "21sh.h"

/*
** Манипулирует курсором, если пользователь нажал alt+LEFT,
** или alt+RIGHT
*/

void        alt_left_right(long c)
{
	int	i;

	i = search_index();
    if (c == ALT_LEFT_ARROW)
        while (i--)
			move_cursor(LEFT_ARROW);
    else
    {
        while (rp()->user_in[i++])
			move_cursor(RIGHT_ARROW);
    }
}
