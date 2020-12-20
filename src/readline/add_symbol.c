/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:18:00 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/20 23:07:36 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	add_symbol_in_str(char *str, char symbol, size_t symbol_index)
{
	size_t str_len;

	str_len = ft_strlen(str);
	ft_memmove(str + symbol_index + 1, str + symbol_index, \
		ft_strlen(str + symbol_index) + 1);
	str[symbol_index] = symbol;
	str[str_len + 1] = '\0';
}

void	readline_putstr(const char *s, int *cur_pos, size_t prompt_len)
{
	ft_putstr_fd(s, STDERR_FILENO);
	cur_pos_after_putstr(cur_pos, prompt_len);
	if (cur_pos[0] > rp(NULL)->ws_col)
	{
		cur_pos[0] = 1;
		cur_pos[1]++;
		ft_putstr_fd(" \r", STDERR_FILENO);
	}
}

void	add_symbol(char c)
{
	int cur_pos[2];

	if (rp(NULL)->max_len <= rp(NULL)->len + 1)
		expand_user_in();
	add_symbol_in_str(rp(NULL)->user_in, c, rp(NULL)->index);
	rp(NULL)->len++;
	tc_clear_till_end();
	readline_putstr(rp(NULL)->user_in + rp(NULL)->index, cur_pos, rp(NULL)->prompt_len);
	move_cursor_to_new_position(cur_pos, rp(NULL)->cur_pos);
	move_cursor(RIGHT_ARROW);
}
