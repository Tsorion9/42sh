/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmove_cursor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:15 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:14:16 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	move_cursor_up(void)
{
	int	last_cur_pos_in_line;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	if (rp(NULL)->cur_pos[1] == 1)
		return ;
	rp(NULL)->cur_pos[1]--;
	last_cur_pos_in_line = search_last_cur_pos_in_line() + 1;
	if (rp(NULL)->cur_pos[0] > last_cur_pos_in_line)
		rp(NULL)->cur_pos[0] = last_cur_pos_in_line;
	if (rp(NULL)->cur_pos[1] == 1 && \
		(long long)rp(NULL)->cur_pos[0] < (long long)rp(NULL)->prompt_len)
		rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
	ret_cur_to_original_pos(prev_cur_pos);
}

static void	move_cursor_down(void)
{
	int	last_cur_pos_in_line;
	int	n;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	n = str_n() + 1;
	if (n == rp(NULL)->cur_pos[1])
		return ;
	rp(NULL)->cur_pos[1]++;
	last_cur_pos_in_line = search_last_cur_pos_in_line() + 1;
	if (rp(NULL)->cur_pos[0] > last_cur_pos_in_line)
		rp(NULL)->cur_pos[0] = last_cur_pos_in_line;
	ret_cur_to_original_pos(prev_cur_pos);
	while (prev_cur_pos[0]-- != 1)
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
}

/*
** Перемещает курсор вверх или вниз.
*/

void		strmove_cursor(long c)
{
	if (c == CTRL_UP)
		move_cursor_up();
	else
		move_cursor_down();
}
