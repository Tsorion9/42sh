#include "21sh.h"

/*
** Очищает строку.
*/

static void	clear_line(int end_cl)
{
	while (rp()->cur_pos[0] > end_cl)
		tc_cursor_left();
	tc_clear_till_end();
}

/*
** Чистит все строки, введенные пользователем.
*/

void		clear_all_line(void)
{
	int n;

	n = str_n() + 1;
	if (n == 1)
	{
		clear_line(rp()->prompt_len);
		rp()->cur_pos[0] = rp()->prompt_len;
		return ;
	}
	while (rp()->cur_pos[0] != 1)
		tc_cursor_left();
	while (rp()->cur_pos[1] != n)
		tc_cursor_down();
	while (rp()->cur_pos[1] > 1)
	{
		clear_line(0);
		tc_cursor_up();
	}
	tc_cursor_n_right(rp()->prompt_len - 1);
	tc_clear_till_end();
}
