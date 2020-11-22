#include "inc21sh.h"

void		delete_symbol_forward(void)
{
	int tmp[2];

	tmp[0] = rp(NULL)->cur_pos[0];
	tmp[1] = rp(NULL)->cur_pos[1];
	move_cursor(RIGHT_ARROW);
	if (tmp[0] != rp(NULL)->cur_pos[0] || tmp[1] != rp(NULL)->cur_pos[1])
		delete_symbol();
}

static void	delete_symbol_in_str(char *str, int symbol_index)
{
	int	str_len = ft_strlen(str) - 1;

	while (symbol_index < str_len)
	{
		str[symbol_index] = str[symbol_index + 1];
		symbol_index++;
	}
	str[symbol_index] = '\0';
}

void		delete_symbol(void)
{
	if (rp(NULL)->index <= 0)
		return ;
	move_cursor(LEFT_ARROW);
	delete_symbol_in_str(rp(NULL)->user_in, rp(NULL)->index);
	tc_save_cursor_pos();
	tc_clear_till_end();
	ft_putstr_fd(rp(NULL)->user_in + rp(NULL)->index, STDERR_FILENO);
	tc_restore_saved_cursor_pos();
	rp(NULL)->len--;
}
