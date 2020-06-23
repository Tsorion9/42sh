#include "21sh.h"
#include <stdio.h>

static void	add_symbol_sup(int tmp[2], char c)
{
	int	i;

	i = search_index();
	ft_memmove(rp()->user_in + i + 1, rp()->user_in + i, \
		ft_strlen(rp()->user_in + i) + 1);
	rp()->user_in[i] = c;
	tmp[0] = rp()->cur_pos[0];
	tmp[1] = rp()->cur_pos[1];
	clear_all_line();
	rp()->cur_pos[0] = tmp[0] + 1;
	rp()->cur_pos[1] = tmp[1];
	rp()->len++;
	ft_putstr_fd(rp()->user_in, STDERR_FILENO);
}

/*
** Добавляет символ и печатает новую строку.
*/

void		add_symbol(char c)
{
	int	tmp[2];

	if (rp()->max_len <= rp()->len + 1)
		expand_user_in();
	add_symbol_sup(tmp, c);
	if (rp()->cur_pos[0] - 1 == rp()->ws_col)
	{
		rp()->cur_pos[0] = 1;
		rp()->cur_pos[1]++;
		if (rp()->cur_pos[1] == str_n() + 1)
			write(STDERR_FILENO, " \r", 2);
		else
		{
			cur_pos_after_putstr(tmp);
			ret_cur_to_original_pos(tmp);
		}
	}
	else
	{
		cur_pos_after_putstr(tmp);
		ret_cur_to_original_pos(tmp);
	}
}

void		delete_symbol_forward(void)
{
	int tmp;

	tmp = rp()->cur_pos[0];
	move_cursor(RIGHT_ARROW);
	if (tmp != rp()->cur_pos[0])
		delete_symbol();
}

int			delete_symbol_sup(int i)
{
	if (rp()->user_in[i] == '\n' || rp()->cur_pos[0] == 1)
	{
		tc_cursor_up();
		if (rp()->cur_pos[1] == 1)
		{
			tc_cursor_n_right(rp()->prompt_len);
			rp()->cur_pos[0] = rp()->prompt_len;
			//if ((rp()->prompt_len + rp()->len - 2) == rp()->ws_col)
			tc_cursor_left();
		}
		return (search_last_cur_pos_in_line() + 2);
	}
	return (rp()->cur_pos[0]);
}

/*
** Удаляет символ и печатает новую строку.
*/

void		delete_symbol(void)
{
	int	len;
	int	i;
	int	tmp[2];

	if ((i = search_index() - 1) < 0)
		return ;
	tmp[0] = delete_symbol_sup(i);
	tmp[1] = rp()->cur_pos[1];
	clear_all_line();
	len = ft_strlen(rp()->user_in);
	while (i < len - 1)
	{
		rp()->user_in[i] = rp()->user_in[i + 1];
		i++;
	}
	rp()->user_in[i] = 0;
	if ((rp()->prompt_len + len - 2) != rp()->ws_col)
		rp()->cur_pos[0] = tmp[0] - 1;
	else
		rp()->cur_pos[0] = tmp[0];
	rp()->cur_pos[1] = tmp[1];
	rp()->len--;
	ft_putstr_fd(rp()->user_in, STDERR_FILENO);
	len = tmp[0] - 1;
	cur_pos_after_putstr(tmp);
	ret_cur_to_original_pos(tmp);
	rp()->cur_pos[0] = len;
}
