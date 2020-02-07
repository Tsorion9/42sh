#include "21sh.h"

void	tc_cursor_left(int *cur_pos)
{
	tputs(tgetstr("le", NULL), STDOUT_FILENO, ft_putint);
	if (!cur_pos)
		return ;
	(*cur_pos)--;
}

void	tc_clear_till_end(void)
{
    tputs(tgetstr("ce", NULL), STDOUT_FILENO, ft_putint);
}

void	tc_cursor_right(int *cur_pos)
{
	tputs(tgetstr("nd", NULL), STDOUT_FILENO, ft_putint);
	if (!cur_pos)
		return ;
	(*cur_pos)++;
}
