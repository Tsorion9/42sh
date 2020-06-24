/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:02 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:03 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Очищает строку.
*/

static void	clear_line(int end_cl)
{
	while (rp(NULL)->cur_pos[0] > end_cl)
		tc_cursor_left();
	tc_clear_till_end();
}

/*
** Чистит все строки, введенные пользователем.
*/

void		clear_all_line(void)
{
	int n;

	n = str_n() + 1;
	if (n == 1)
	{
		clear_line(rp(NULL)->prompt_len);
		rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
		return ;
	}
	while (rp(NULL)->cur_pos[0] != 1)
		tc_cursor_left();
	while (rp(NULL)->cur_pos[1] != n)
		tc_cursor_down();
	while (rp(NULL)->cur_pos[1] > 1)
	{
		clear_line(0);
		tc_cursor_up();
	}
	tc_cursor_n_right(rp(NULL)->prompt_len - 1);
	tc_clear_till_end();
}
