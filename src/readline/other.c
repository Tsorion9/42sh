/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:39 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/04 00:00:47 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		move_cursor_to_new_position(int *actual_cur_pos, int *new_cur_pos)
{
	while (actual_cur_pos[0] > new_cur_pos[0])
	{
		tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[0]--;
	}
	while (actual_cur_pos[1] > new_cur_pos[1])
	{
		tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[1]--;
	}
	while (actual_cur_pos[1] < new_cur_pos[1])
	{
		tputs(tgetstr("do", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[1]++;
	}
	while (actual_cur_pos[0] < new_cur_pos[0])
	{
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
		actual_cur_pos[0]++;
	}
}

void		delete_last_word(void)
{
	while (rp(NULL)->index)
	{
		if (ft_isspace(rp(NULL)->user_in[rp(NULL)->index]))
			delete_symbol();
		else
			break ;
	}
	while (rp(NULL)->index)
	{
		if (!ft_isspace(rp(NULL)->user_in[rp(NULL)->index]))
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
