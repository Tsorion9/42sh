/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:55 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:57 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

void					fill_t_float(long double x, t_float *num, int precision)
{
	num->mant = *((unsigned long int *)&x);
	num->exp = *(unsigned short *)((char *)&x + sizeof(unsigned long int));
	num->sign = num->exp & (((unsigned short)1) << 15);
	num->exp = num->exp & ~(((unsigned short)1) << 15);
	num->mant_mask = (((unsigned long int)1) << 63);
	num->mask_shift = 0;
	num->precision = precision;
	if (num->precision < 0)
		num->precision = 6;
}

int						abs_(int x)
{
	return (x >= 0 ? x : -x);
}

/*
**	8 < 10 < 16
*/

void					cut_float(t_float *num, int *power_of2)
{
	int					ignore_pow;

	ignore_pow = num->precision * 4 + CRUTCH_FLOAT_PRECISION_CONSTANT;
	if (*power_of2 < -ignore_pow)
		*power_of2 = -ignore_pow;
}

char					*eval_power_sum(t_float *num, int power_of2)
{
	static char			res[LD_MAX_DIGITS];
	static t_decimal	total;
	static t_decimal	current;
	static t_decimal	accum;

	cut_float(num, &power_of2);
	positive_ascii_to(&accum, "0");
	positive_ascii_to(&total, power_of2 > 0 ? "2" : "0.5");
	power_positive_decimal(&total, abs_(power_of2));
	while (num->mask_shift < 64)
	{
		if (num->mant_mask >> num->mask_shift & num->mant)
		{
			positive_ascii_to(&current, "0.5");
			power_positive_decimal(&current, num->mask_shift);
			add_positive_decimal(&accum, &current);
		}
		num->mask_shift++;
	}
	multiply_positive_decimal(&accum, &total);
	if (num->sign)
		accum.is_negative = 1;
	to_ascii(accum, res);
	return (res);
}
