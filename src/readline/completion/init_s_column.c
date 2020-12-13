/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_s_column.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 11:08:31 by nriker            #+#    #+#             */
/*   Updated: 2020/12/13 21:32:42 by alexbuyanov      ###   ########.fr       */
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
