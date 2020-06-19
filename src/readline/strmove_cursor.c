#include "21sh.h"

static void move_cursor_up(void)
{
    int     last_cur_pos_in_line;
    int     prev_cur_pos[2];

    prev_cur_pos[0] = rp()->cur_pos[0];
    prev_cur_pos[1] = rp()->cur_pos[1];
    if (rp()->cur_pos[1] == 1)
            return ;
    rp()->cur_pos[1]--;
    last_cur_pos_in_line = search_last_cur_pos_in_line() + 1;
    if (rp()->cur_pos[0] > last_cur_pos_in_line)
        rp()->cur_pos[0] = last_cur_pos_in_line;
    if (rp()->cur_pos[1] == 1 && (long long)rp()->cur_pos[0] < (long long)rp()->prompt_len)
        rp()->cur_pos[0] = rp()->prompt_len;
    ret_cur_to_original_pos(prev_cur_pos);
}

static void move_cursor_down(void)
{
    int     last_cur_pos_in_line;
    int     n;
    int     prev_cur_pos[2];

    prev_cur_pos[0] = rp()->cur_pos[0];
    prev_cur_pos[1] = rp()->cur_pos[1];
    n = str_n() + 1;
    if (n == rp()->cur_pos[1])
        return ;
    rp()->cur_pos[1]++;
    last_cur_pos_in_line = search_last_cur_pos_in_line() + 1;
    if (rp()->cur_pos[0] > last_cur_pos_in_line)
        rp()->cur_pos[0] = last_cur_pos_in_line;
    ret_cur_to_original_pos(prev_cur_pos);
    while (prev_cur_pos[0]-- != 1)
        tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
}

/*
** Перемещает курсор вверх или вниз.
*/

void        strmove_cursor(long c)
{
    if (c == CTRL_UP)
        move_cursor_up();
    else
        move_cursor_down();
}
