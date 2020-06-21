#include "21sh.h"

void	tc_cursor_left(void)
{
	tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
	rp()->cur_pos[0]--;
}

void	tc_clear_till_end(void)
{
    tputs(tgetstr("ce", NULL), STDERR_FILENO, ft_putint);
}

void	tc_cursor_right(void)
{
	tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
	rp()->cur_pos[0]++;
}

void	tc_cursor_up(void)
{
	tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
	rp()->cur_pos[0] = 1;
	rp()->cur_pos[1] -= 1;
}

void	tc_cursor_down(void)
{
	write(STDERR_FILENO, "\n", 1);
	rp()->cur_pos[1]++;
}

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

