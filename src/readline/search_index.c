/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_index.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:09 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:14:10 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Index of symbol under cursor
*/

int		search_index(void)
{
	int	n;
	int	i;
	int	cur_pos_col;

	n = 1;
	i = 0;
	if (rp(NULL)->cur_pos[1] == 1)
		return (rp(NULL)->cur_pos[0] - rp(NULL)->prompt_len);
	cur_pos_col = rp(NULL)->prompt_len;
	while (n < rp(NULL)->cur_pos[1])
	{
		if (rp(NULL)->user_in[i] == '\n' || cur_pos_col >= rp(NULL)->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		i++;
	}
	i += rp(NULL)->cur_pos[0] - 1;
	return (i);
}

void	inverse_search_index(int cur_pos[2], int index)
{
	int	i;

	cur_pos[0] = rp(NULL)->prompt_len;
	cur_pos[1] = 1;
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
