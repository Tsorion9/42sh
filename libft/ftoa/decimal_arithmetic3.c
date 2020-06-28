/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_arithmetic3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:18 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:20 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

/*
**	Fill repr
**  In line 24 end points to last digit!
*/

void		positive_ascii_to(t_decimal *repr, char *s)
{
	repr->is_negative = 0;
	repr->after_dot = nchar_after_dot(s);
	repr->end = repr->buff + LD_MAX_DIGITS - 1;
	repr->start = repr->end - ndigits(s) + 1;
	copy_digits_numbers(s, repr->start);
}

/*
**Addition functions below
*/

/*
** return number of excessive digits
*/

int			shift_excessive_digits(t_decimal *a, t_decimal *b, char *tmp)
{
	int	i;
	int	nchar_a;
	int	nchar_b;

	nchar_a = a->after_dot;
	nchar_b = b->after_dot;
	i = 0;
	while (nchar_a > nchar_b)
	{
		nchar_b++;
		tmp[i] = *(a->end);
		a->end--;
		i++;
	}
	while (nchar_b > nchar_a)
	{
		nchar_a++;
		tmp[i] = *(b->end);
		b->end--;
		i++;
	}
	return (i);
}

/*
** case when b ended
*/

void		single_digit_a(t_decimal *a, char **res, int *carry)
{
	**res = (*(a->end) + *carry) % 10;
	*carry = (*(a->end) + *carry) / 10;
	a->end--;
	(*res)++;
}

/*
** case when a ended
*/

void		single_digit_b(t_decimal *b, char **res, int *carry)
{
	**res = (*(b->end) + *carry) % 10;
	*carry = (*(b->end) + *carry) / 10;
	b->end--;
	(*res)++;
}

/*
** case when both numbers not ended
*/

void		single_digit_both(t_decimal *a, t_decimal *b, \
				char **res, int *carry)
{
	**res = (*(a->end) + *(b->end) + *carry) % 10;
	*carry = (*(a->end) + *(b->end) + *carry) / 10;
	a->end--;
	b->end--;
	(*res)++;
}
