/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/10/13 20:43:13 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	tc_cursor_left(void)
{
	tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[0]--;
}

/*
** Очистка до конца строки.
** Аналог - функция clear_line
** clear_all_line - вызов в цикле этой функции, для очистки всей команды
*/

void	tc_clear_till_end(void)
{
	tputs(tgetstr("ce", NULL), STDERR_FILENO, ft_putint);
}

void	tc_cursor_right(void)
{
	tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[0]++;
}

void	tc_cursor_up(void)
{
	tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[0] = 1;
	rp(NULL)->cur_pos[1] -= 1;
}

void	tc_cursor_down(void)
{
	write(STDERR_FILENO, "\n", 1);
	rp(NULL)->cur_pos[1]++;
}
