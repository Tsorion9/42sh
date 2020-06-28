/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_arithmetic4.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:29 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:32 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

/*
**	Fill res with digits
**	Ignore possible overflow yet
**	res will be terminated by -1
*/

void		adder_decimal(t_decimal *a, t_decimal *b, char *res)
{
	int		carry;

	carry = 0;
	while (a->start <= a->end || b->start <= b->end)
	{
		if (a->start > a->end)
			single_digit_b(b, &res, &carry);
		else if (b->start > b->end)
			single_digit_a(a, &res, &carry);
		else
			single_digit_both(a, b, &res, &carry);
	}
	if (carry)
		*(res++) = carry;
	else
		((*res) = -1);
	*res = -1;
}

void		copy_from_buf(char *buf, t_decimal *a)
{
	a->start = a->end;
	while (*buf != -1)
	{
		*(a->start) = *buf;
		a->start--;
		buf++;
	}
	a->start++;
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}

/*
**  Add 2 numbers in-place (result is stored in a)
**  inverse number will be stored here in line 66;
*/

void		add_positive_decimal(t_decimal *a, t_decimal *b)
{
	char	tmp[LD_MAX_DIGITS];

	adder_decimal(a, b, tmp + shift_excessive_digits(a, b, tmp));
	a->end = a->buff + LD_MAX_DIGITS - 1;
	b->end = b->buff + LD_MAX_DIGITS - 1;
	copy_from_buf(tmp, a);
	a->after_dot = max(a->after_dot, b->after_dot);
}

/*
** Multiplication functions below
** //end points to last digit! in line 86
**  //end points to last digit!
*/

void		mul_digit(t_decimal *a, t_decimal *b, \
					int degree, t_decimal *partial_product)
{
	int	carry;

	partial_product->end = partial_product->buff + LD_MAX_DIGITS - 1;
	partial_product->start = partial_product->end;
	while (degree--)
		*(partial_product->start--) = 0;
	carry = 0;
	while (a->start <= a->end)
	{
		*(partial_product->start) = (*(b->end) * *(a->end) + carry) % 10;
		carry = (*(b->end) * *(a->end) + carry) / 10;
		a->end--;
		partial_product->start--;
	}
	partial_product->start++;
	if (carry)
	{
		partial_product->start--;
		*(partial_product->start) = carry;
	}
	a->end = a->buff + LD_MAX_DIGITS - 1;
}
