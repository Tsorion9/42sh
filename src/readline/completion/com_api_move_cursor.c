/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_move_cursor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 13:47:25 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 13:00:03 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		com_api_return_curs_to_position(int columns_right)
{
	while (columns_right--)
	{
		tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
	}
}

void		com_api_return_curs_to_line(void)
{
	int raws;

	raws = rp(NULL)->competitions_raws;
	if (raws)
		while (raws--)
		{
			tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
		}
	rp(NULL)->competitions_raws = 0;
}

void		com_api_move_curs_to_prev_pos(void)
{
	t_rp	*trp;
	int		i;
	int		z;

	trp = rp(NULL);
	i = search_index(trp->cur_pos, trp->prompt_len);
	if (trp->prev_pos_curs != i)
	{
		z = trp->prev_pos_curs;
		while (i != (z + 1))
		{
			move_cursor(LEFT_ARROW);
			i--;
		}
		move_cursor(LEFT_ARROW);
	}
	trp->prev_pos_curs = 0;
}

void		com_api_move_curs_to_end_line(void)
{
	t_rp		*trp;
	int			i;

	trp = rp(NULL);
	i = search_index(trp->cur_pos, trp->prompt_len);
	trp->prev_pos_curs = i;
	if (trp->user_in[i])
	{
		while (trp->user_in[i++])
			move_cursor(RIGHT_ARROW);
		move_cursor(RIGHT_ARROW);
	}
	trp->column_end_of_line = com_api_get_curs_col() - 1;
}
