/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:51 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:52 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

char		*normal_case(t_float *num)
{
	return (eval_power_sum(num, num->exp - 16383));
}

char		*exp_all_zeros(t_float *num)
{
	if (!num->mant)
		return (num->sign ? "-0.0" : "0.0");
	return (eval_power_sum(num, -16382));
}

/*
** //62-0 bits of mant == 0
*/

char		*exp_all_ones(t_float *num)
{
	if (!(num->mant & ~num->mant_mask))
		return (num->sign ? "-inf" : "inf");
	return ("NaN");
}

char		*ftoa(long double x, int precision)
{
	t_float	num;

	fill_t_float(x, &num, precision);
	if (!~((num.exp << 1) + 1))
		return (exp_all_ones(&num));
	else if ((num.exp << 1) != 0)
		return (exp_all_zeros(&num));
	else
		return (normal_case(&num));
}
