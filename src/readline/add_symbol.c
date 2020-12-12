/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_symbol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:18:00 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/01 22:06:44 by mphobos          ###   ########.fr       */
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

void	add_symbol(char c)
{
	if (rp(NULL)->max_len <= rp(NULL)->len + 1)
		expand_user_in();
	add_symbol_in_str(rp(NULL)->user_in, c, rp(NULL)->index);
	rp(NULL)->len++;
	tc_clear_till_end();
	tc_save_cursor_pos();
	ft_putstr_fd(rp(NULL)->user_in + rp(NULL)->index, STDERR_FILENO);
	tc_restore_saved_cursor_pos();
	move_cursor(RIGHT_ARROW);
}
