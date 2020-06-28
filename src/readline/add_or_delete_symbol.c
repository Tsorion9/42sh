/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_delete_symbol.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:10:07 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 19:41:33 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	add_symbol_sup(int tmp[2], char c)
{
	int	i;

	i = search_index();
	ft_memmove(rp(NULL)->user_in + i + 1, rp(NULL)->user_in + i, \
		ft_strlen(rp(NULL)->user_in + i) + 1);
	rp(NULL)->user_in[i] = c;
	tmp[0] = rp(NULL)->cur_pos[0];
	tmp[1] = rp(NULL)->cur_pos[1];
	clear_all_line();
	rp(NULL)->cur_pos[0] = tmp[0] + 1;
	rp(NULL)->cur_pos[1] = tmp[1];
	rp(NULL)->len++;
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
}

/*
** Добавляет символ и печатает новую строку.
*/

void		add_symbol(char c)
{
	int	tmp[2];

	if (rp(NULL)->max_len <= rp(NULL)->len + 1)
		expand_user_in();
	add_symbol_sup(tmp, c);
	if (rp(NULL)->cur_pos[0] - 1 == rp(NULL)->ws_col)
	{
		rp(NULL)->cur_pos[0] = 1;
		rp(NULL)->cur_pos[1]++;
		if (rp(NULL)->cur_pos[1] == str_n() + 1)
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
	int tmp[2];

	tmp[0] = rp(NULL)->cur_pos[0];
	tmp[1] = rp(NULL)->cur_pos[1];
	move_cursor(RIGHT_ARROW);
	if (tmp[0] != rp(NULL)->cur_pos[0] || tmp[1] != rp(NULL)->cur_pos[1])
		delete_symbol();
}

int			delete_symbol_sup(int i)
{
	if (rp(NULL)->user_in[i] == '\n' || rp(NULL)->cur_pos[0] == 1)
	{
		tc_cursor_up();
		if (rp(NULL)->cur_pos[1] == 1)
		{
			tc_cursor_n_right(rp(NULL)->prompt_len);
			rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
			if ((rp(NULL)->prompt_len + rp(NULL)->len - 2) != rp(NULL)->ws_col)
				tc_cursor_left();
		}
		return (search_last_cur_pos_in_line() + 2);
	}
	return (rp(NULL)->cur_pos[0]);
}

/*
** Удаляет символ и печатает новую строку.
*/

void		delete_symbol(void)
{
	int	i;
	int	tmp[2];

	if ((i = search_index() - 1) < 0)
		return ;
	tmp[0] = delete_symbol_sup(i);
	tmp[1] = rp(NULL)->cur_pos[1];
	clear_all_line();
	while (i < (int)rp(NULL)->len - 1)
	{
		rp(NULL)->user_in[i] = rp(NULL)->user_in[i + 1];
		i++;
	}
	rp(NULL)->user_in[i] = 0;
	rp(NULL)->cur_pos[0] = tmp[0] - 1;
	if (((rp(NULL)->prompt_len + rp(NULL)->len - 2) % rp(NULL)->ws_col == 0) &&\
		!ft_strchr(rp(NULL)->user_in, '\n'))
		rp(NULL)->cur_pos[0] = tmp[0];
	rp(NULL)->cur_pos[1] = tmp[1];
	rp(NULL)->len--;
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
	i = tmp[0] - 1;
	cur_pos_after_putstr(tmp);
	ret_cur_to_original_pos(tmp);
	rp(NULL)->cur_pos[0] = i;
}
