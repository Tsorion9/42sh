/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_cur_pos.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:04 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 19:42:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "stdio.h"

int		search_last_cur_pos_in_line_sup(int cur_pos_col, int i)
{
	if (rp(NULL)->cur_pos[1] == 1)
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

int		search_last_cur_pos_in_line(void)
{
	int n;
	int i;
	int cur_pos_col;

	n = 1;
	i = 0;
	cur_pos_col = rp(NULL)->prompt_len;
	while (n != rp(NULL)->cur_pos[1])
	{
		if (rp(NULL)->user_in[i] == '\n' || cur_pos_col > rp(NULL)->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		i++;
	}
	return (search_last_cur_pos_in_line_sup(1, i));
}

/*
** Записывает в указатель cur_pos позицию
** курсора после вывода строки (rp(NULL)->user_in).
*/

void	cur_pos_after_putstr(int *cur_pos)
{
	int	i;
	int	n;
	int	cur_pos_col;

	cur_pos[1] = str_n() + 1;
	if (cur_pos[1] == 1)
		cur_pos[0] = ft_strlen(rp(NULL)->user_in) + rp(NULL)->prompt_len;
	else
	{
		i = 0;
		n = cur_pos[1] - 1;
		cur_pos_col = rp(NULL)->prompt_len;
		while (n)
		{
			if (rp(NULL)->user_in[i] == '\n' || cur_pos_col >= rp(NULL)->ws_col)
			{
				cur_pos_col = 0;
				n--;
			}
			cur_pos_col++;
			i++;
		}
		cur_pos[0] = ft_strlen(rp(NULL)->user_in) - i + 1;
	}
}
