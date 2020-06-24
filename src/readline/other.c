/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:39 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:40 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		ret_cur_to_original_pos(int *prev_cur_pos)
{
	while (prev_cur_pos[0] > rp(NULL)->cur_pos[0])
	{
		tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
		prev_cur_pos[0]--;
	}
	while (prev_cur_pos[1] > rp(NULL)->cur_pos[1])
	{
		tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
		prev_cur_pos[1]--;
	}
	while (prev_cur_pos[1] < rp(NULL)->cur_pos[1])
	{
		tputs(tgetstr("do", NULL), STDERR_FILENO, ft_putint);
		prev_cur_pos[1]++;
	}
	while (prev_cur_pos[0] < rp(NULL)->cur_pos[0])
	{
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
		prev_cur_pos[0]++;
	}
}

void		delete_last_word(void)
{
	int i;

	while ((i = search_index() - 1) >= 0)
	{
		if (ft_isspace(rp(NULL)->user_in[i]))
			delete_symbol();
		else
			break ;
	}
	while ((i = search_index() - 1) >= 0)
	{
		if (!ft_isspace(rp(NULL)->user_in[i]))
			delete_symbol();
		else
			break ;
	}
}

/*
** This function probably should be added to libft
*/

int			ft_isspace(char c)
{
	if (c == ' ' || c == '\f' || c == '\r' \
			|| c == '\t' || c == '\v')
		return (1);
	return (0);
}
