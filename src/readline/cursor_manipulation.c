#include "21sh.h"

/*
** Очищает строку
*/

void        clear_line(int cur_pos, int end_cl)
{
    while (cur_pos != end_cl)
		  tc_cursor_left(&cur_pos);
	tc_clear_till_end();
}

/*
** Манипулирует курсором, если пользователь нажал alt+LEFT,
** или alt+RIGHT
*/

void        alt_left_right(long c, int *cur_pos, char *user_in)
{
    int user_in_len;

    if (c == ALT_LEFT_ARROW)
        while (*cur_pos != 3)
			tc_cursor_left(cur_pos);
    else
    {
        user_in_len = ft_strlen(user_in) + 2;
        while (*cur_pos <= user_in_len)
			tc_cursor_right(cur_pos);
    }
}

/*
** Перемещает курсор вправо, либо влево
*/

void        move_cursor(long c, int *cur_pos, char *user_in)
{
    if (c == LEFT_ARROW && *cur_pos >= 4)
	    tc_cursor_left(cur_pos);
    else if (c == RIGHT_ARROW && (size_t)*cur_pos <= ft_strlen(user_in) + 2)
		  tc_cursor_right(cur_pos);
}
