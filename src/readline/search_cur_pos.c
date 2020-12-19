/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cur_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:04 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/19 13:42:59 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "stdio.h"

static int	search_last_cur_pos_in_line_sup(int cur_pos_col, int i, int line)
{
	if (line == 1)
		cur_pos_col = rp(NULL)->prompt_len;
	while (rp(NULL)->user_in[i] != '\n' && cur_pos_col < rp(NULL)->ws_col - 1\
			&& rp(NULL)->user_in[i])
	{
		cur_pos_col++;
		i++;
	}
	if (rp(NULL)->user_in[i] == '\n')
		cur_pos_col--;
	return (cur_pos_col);
}

/*
** Ищет последнюю позицию курсора по ширине для
** актуальной позиции курсора по высоте (rp(NULL)->cur_pos[1]).
*/

int			search_last_cur_pos_in_line(int line)
{
	int n;
	int i;
	int cur_pos_col;

	n = 1;
	i = 0;
	cur_pos_col = rp(NULL)->prompt_len;
	while (n != line)
	{
		if (rp(NULL)->user_in[i] == '\n' || cur_pos_col > rp(NULL)->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		i++;
	}
	return (search_last_cur_pos_in_line_sup(1, i, line));
}

void		cur_pos_after_putstr(int *cur_pos, size_t prompt_len)
{
	int	i;
	int	ws_col;
	int	a;

	ws_col = rp(NULL)->ws_col;
	a = prompt_len / ws_col;
	cur_pos[0] = prompt_len - ws_col * a;
	cur_pos[1] = a + 1;
	i = 0;
	while (rp(NULL)->user_in[i])
	{
		if (rp(NULL)->user_in[i] == '\n' || cur_pos[0] >= rp(NULL)->ws_col)
		{
			cur_pos[0] = 0;
			cur_pos[1]++;
		}
		cur_pos[0]++;
		i++;
	}
}
