#include "21sh.h"

/*
** Очищает строку.
*/

static void clear_line(int end_cl)
{
    while (rp()->cur_pos[0] > end_cl)
		  tc_cursor_left();
	tc_clear_till_end();
}

/*
** Чистит все строки, введенные пользователем.
*/

void        clear_all_line(void)
{
    int n;

    n = str_n() + 1;
    if (n == 1)
    {
        clear_line(3);
        rp()->cur_pos[0] = 3;
        return ;
    }
    //if (n == 3)
    //    printf("2\n");
    while (rp()->cur_pos[0] != 1)
        tc_cursor_left();
    while (rp()->cur_pos[1] != n)
        tc_cursor_down();
    while (rp()->cur_pos[1] > 1)
    {
        clear_line(0);
        tc_cursor_up();
    }
    tc_cursor_right();
    tc_cursor_right();
    tc_clear_till_end();
}
