/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:08 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 19:42:15 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Перемещает курсор на одну позицию влево.
*/

static void	move_cursor_left(void)
{
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	if (rp(NULL)->cur_pos[0] == 1)
	{
		rp(NULL)->cur_pos[1]--;
		rp(NULL)->cur_pos[0] = search_last_cur_pos_in_line() + 1;
	}
	else if ((size_t)rp(NULL)->cur_pos[0] == (size_t)rp(NULL)->prompt_len && \
		rp(NULL)->cur_pos[1] == 1)
		return ;
	else
		rp(NULL)->cur_pos[0]--;
	ret_cur_to_original_pos(prev_cur_pos);
}

/*
** Перемещает курсор на одну позицию вправо.
*/

static void	move_cursor_right(void)
{
	int	i;
	int	prev_cur_pos[2];

	prev_cur_pos[0] = rp(NULL)->cur_pos[0];
	prev_cur_pos[1] = rp(NULL)->cur_pos[1];
	i = search_index();
	if (rp(NULL)->user_in[i] == '\n' ||\
			rp(NULL)->cur_pos[0] == rp(NULL)->ws_col)
	{
		rp(NULL)->cur_pos[0] = 1;
		rp(NULL)->cur_pos[1]++;
	}
	else if (rp(NULL)->user_in[i] != 0)
		rp(NULL)->cur_pos[0]++;
	ret_cur_to_original_pos(prev_cur_pos);
}

/*
** Перемещает курсор на одну позицию.
*/

void		move_cursor(long c)
{
	if (c == LEFT_ARROW)
		move_cursor_left();
	else
		move_cursor_right();
}
