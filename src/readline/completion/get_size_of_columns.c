/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_size_of_columns.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:04:58 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 09:05:29 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	get_mas_width(char **buf, t_column *cl)
{
	int i;

	if (!buf)
	{
		cl->buf_size = 0;
		return ;
	}
	i = -1;
	while (buf[++i])
	{
		if ((int)ft_strlen(buf[i]) > cl->max_width)
		{
			cl->max_width = ft_strlen(buf[i]);
		}
	}
	cl->buf_size = i;
}

static void	get_one_column(t_column *cl)
{
	cl->width_column = 8;
	while (cl->max_width >= cl->width_column)
		cl->width_column += 8;
}

static void	get_col_raw(t_column *cl)
{
	int		value;

	value = 0;
	cl->col_got = cl->col / cl->width_column;
	if (!cl->col_got)
		cl->col_got = 1;
	cl->row_got = ((cl->buf_size - 1) / cl->col_got) + 1;
	while (cl->col_got > 1)
	{
		value = ((cl->buf_size - 1) / (cl->col_got - 1)) + 1;
		if (cl->row_got < value)
			break ;
		cl->col_got--;
	}
}

void		get_size_of_columns(char **buf, t_column *cl)
{
	cl->buf_size = 0;
	cl->row_got = 0;
	cl->col_got = 0;
	cl->max_width = 0;
	cl->width_column = 0;
	get_mas_width(buf, cl);
	if (!cl->buf_size)
		return ;
	get_one_column(cl);
	get_col_raw(cl);
}
