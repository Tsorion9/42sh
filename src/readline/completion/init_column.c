/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_column.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 21:02:55 by nriker            #+#    #+#             */
/*   Updated: 2020/12/29 21:02:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	create_t_column(t_column **cl)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (!(*cl = (t_column*)malloc(sizeof(t_column))))
		return ;
	(*cl)->col = w.ws_col;
	(*cl)->row = w.ws_row;
	(*cl)->buf_size = 0;
	(*cl)->row_got = 0;
	(*cl)->col_got = 0;
	(*cl)->max_width = 0;
	(*cl)->width_column = 0;
}
