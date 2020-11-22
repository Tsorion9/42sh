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
#include <stdio.h>

static void	add_symbol_sup(int tmp[2], char c)
{
	int	i;

	i = search_index();
	ft_memmove(rp(NULL)->user_in + i + 1, rp(NULL)->user_in + i, \
		ft_strlen(rp(NULL)->user_in + i) + 1);
	rp(NULL)->user_in[i] = c;
	tmp[0] = rp(NULL)->cur_pos[0];
	tmp[1] = rp(NULL)->cur_pos[1];
	tc_clear_till_end();
	rp(NULL)->cur_pos[0] = tmp[0] + 1;
	rp(NULL)->cur_pos[1] = tmp[1];
	rp(NULL)->len++;
	ft_putstr_fd(rp(NULL)->user_in + i, STDERR_FILENO);
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
			move_cursor_to_new_position(tmp, rp(NULL)->cur_pos);
		}
	}
	else
	{
		cur_pos_after_putstr(tmp);
		move_cursor_to_new_position(tmp, rp(NULL)->cur_pos);
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

/*static void	print_cur_pos(int *cur_pos)
{
	printf("\n x = %d , y = %d \n", cur_pos[0], cur_pos[1]);
}*/

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
	int	symbol_index;

	symbol_index = search_index() - 1;
	if (symbol_index < 0)
		return;
	delete_symbol_in_str(rp(NULL)->user_in, symbol_index);
	move_cursor(LEFT_ARROW);
	tc_save_cursor_pos();
	tc_clear_till_end();
	ft_putstr_fd(rp(NULL)->user_in + symbol_index, STDERR_FILENO);
	tc_restore_saved_cursor_pos();
}
