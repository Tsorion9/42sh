/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_api.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/29 21:47:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	tc_cursor_left(void)
{
	tputs(tgetstr("le", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[0]--;
}

void	tc_cursor_right(void)
{
	tputs(tgetstr("nd", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[0]++;
}

void	tc_cursor_up(void)
{
	tputs(tgetstr("up", NULL), STDERR_FILENO, ft_putint);
	rp(NULL)->cur_pos[1] -= 1;
}

void	tc_cursor_down(void)
{
	write(STDERR_FILENO, "\n", 1);
	rp(NULL)->cur_pos[1]++;
}

void	tc_clear_till_end(void)
{
	tputs(tgetstr("cd", NULL), STDERR_FILENO, ft_putint);
}
