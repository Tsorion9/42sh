/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_n.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:13 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:14:14 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static int	str_n_sup(char *user_in, int n)
{
	unsigned short	cur_pos_col;

	cur_pos_col = 1;
	while (*user_in)
	{
		if (*user_in == '\n' || cur_pos_col >= rp(NULL)->ws_col)
		{
			cur_pos_col = 0;
			n++;
		}
		cur_pos_col++;
		user_in++;
	}
	return (n);
}

/*
** Возвращает количество строк, занимаемых в терминале,
** командой (rp(NULL)->user_in).
*/

int			str_n(void)
{
	char			*user_in;
	int				n;
	unsigned short	cur_pos_col;

	user_in = rp(NULL)->user_in;
	n = 0;
	cur_pos_col = rp(NULL)->prompt_len;
	while (*user_in && *user_in != '\n' && cur_pos_col <= rp(NULL)->ws_col)
	{
		cur_pos_col++;
		user_in++;
	}
	if ((*user_in == '\n' || cur_pos_col > rp(NULL)->ws_col) && *user_in)
	{
		n++;
		user_in++;
	}
	return (str_n_sup(user_in, n));
}
