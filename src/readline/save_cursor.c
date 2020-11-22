#include "inc21sh.h"

void	tc_save_cursor_pos(void)
{
	tputs(tgetstr("sc", NULL), STDERR_FILENO, ft_putint);
}

void	tc_restore_saved_cursor_pos(void)
{
	tputs(tgetstr("rc", NULL), STDERR_FILENO, ft_putint);
}
