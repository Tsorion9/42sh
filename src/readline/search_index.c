/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:09 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/04 00:15:26 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Index of symbol under cursor
*/

int		search_index(int *cur_pos, size_t prompt_len)
{
	int	n;
	int	i;
	int	cur_pos_col;

	n = 1;
	i = 0;
	if (cur_pos[1] == 1)
		return (cur_pos[0] - prompt_len);
	cur_pos_col = prompt_len;
	while (n < cur_pos[1])
	{
		if (rp(NULL)->user_in[i] == '\n' || cur_pos_col >= rp(NULL)->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		i++;
	}
	i += cur_pos[0] - 1;
	return (i);
}

void	inverse_search_index(int cur_pos[2], int index, size_t prompt_len)
{
	int	i;

	int ws_col = rp(NULL)->ws_col;
	int a = prompt_len / ws_col;
	int b = ws_col * a;
	if (ws_col || a || b)
	cur_pos[0] = (prompt_len - ws_col * a) + 1;
	cur_pos[1] = a + 1;
	i = 0;
	while (i < index && rp(NULL)->user_in[i])
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
