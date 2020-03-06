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

void	tc_cursor_up(int *cur_pos)
{
	tputs(tgetstr("up", NULL), STDOUT_FILENO, ft_putint);
	if (!cur_pos)
		return ;
	*cur_pos = 1;
	*(cur_pos + 1) -= 1;
}

void	tc_cursor_down(int *cur_pos)
{
	write(STDOUT_FILENO, "\n", 1);
	if (!cur_pos)
		return ;
	cur_pos[1]++;
}
