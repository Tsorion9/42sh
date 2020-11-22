#include "inc21sh.h"

static void	add_symbol_in_str(char *str, char symbol, int symbol_index)
{
	ft_memmove(str + symbol_index + 1, str + symbol_index, \
		ft_strlen(str + symbol_index) + 1);
	str[symbol_index] = symbol;
}

void		add_symbol(char c)
{
	if (rp(NULL)->max_len <= rp(NULL)->len + 1)
		expand_user_in();
	add_symbol_in_str(rp(NULL)->user_in, c, rp(NULL)->index);
	tc_clear_till_end();
	tc_save_cursor_pos();
	ft_putstr_fd(rp(NULL)->user_in + rp(NULL)->index, STDERR_FILENO);
	tc_restore_saved_cursor_pos();
	move_cursor(RIGHT_ARROW);
	rp(NULL)->len++;
}
