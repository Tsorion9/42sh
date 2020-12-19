/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_column.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/19 09:03:31 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/12/19 09:04:28 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	printtt(int width, char *buf)
{
	ft_putstr(buf);
	width -= ft_strlen(buf);
	while (width--)
		ft_putchar(' ');
}

void	print_column(char **buf, t_column *cl)
{
	int	i;
	int	y;
	int	raw;
	int	col;
	int buf_s;

	i = -1;
	get_size_of_columns(buf, cl);
	buf_s = cl->buf_size;
	cl->buf_size += 1;
	raw = cl->row_got;
	while (raw--)
	{
		i++;
		y = i;
		col = cl->col_got;
		while (col--)
		{
			if (y < buf_s)
				printtt(cl->width_column - 1, buf[y]);
			y += cl->row_got;
		}
		ft_putchar('\n');
	}
}
