/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_arithmetic5.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:37 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:39 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

/*
** in line 32 //end points to last digit!
*/

void			copy_t_decimal(t_decimal *src, t_decimal *dst)
{
	char	*tmp;

	tmp = src->end;
	while (tmp >= src->start)
	{
		*(dst->end) = *tmp;
		dst->end--;
		tmp--;
	}
	dst->end++;
	dst->start = dst->end;
	dst->end = dst->buff + LD_MAX_DIGITS - 1;
	dst->after_dot = src->after_dot;
	dst->is_negative = src->is_negative;
}

void			adjust_dot_if_needed(t_decimal *a)
{
	while (a->after_dot > a->end - a->start + 1)
	{
		a->start--;
		*(a->start) = 0;
	}
}

/*
**  Multiply 2 DIFFERENT numbers in-place (result is stored in a)
**	In case of square, you need to copy  the first operand
** //end points to last digit! in line 72
*/

void			multiply_positive_decimal(t_decimal *a, t_decimal *b)
{
	static t_decimal	total;
	static t_decimal	partial_product;
	int					degree;
	int					after_dot_new;

	positive_ascii_to(&partial_product, "0");
	positive_ascii_to(&total, "0");
	degree = 0;
	while (b->end >= b->start)
	{
		if (*b->end)
		{
			mul_digit(a, b, degree, &partial_product);
			add_positive_decimal(&total, &partial_product);
		}
		b->end--;
		degree++;
	}
	b->end = b->buff + LD_MAX_DIGITS - 1;
	after_dot_new = a->after_dot + b->after_dot;
	copy_t_decimal(&total, a);
	a->after_dot = after_dot_new;
	adjust_dot_if_needed(a);
}
