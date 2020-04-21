/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_arithmetic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:04 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:08 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

/*
** Power functions below
*/

void			init_t_decimal(t_decimal *x)
{
	x->end = x->buff + LD_MAX_DIGITS - 1;
	x->start = x->end;
	x->after_dot = 0;
	x->is_negative = 0;
}

void			square_positive_decimal(t_decimal *x)
{
	t_decimal tmp;

	init_t_decimal(&tmp);
	copy_t_decimal(x, &tmp);
	multiply_positive_decimal(x, &tmp);
}

/*
**	Only positive powers
*/

void			power_positive_decimal(t_decimal *x, int pow)
{
	int			current_power;
	t_decimal	result;
	t_decimal	current_value;

	if (!pow)
		positive_ascii_to(x, "1");
	init_t_decimal(&current_value);
	positive_ascii_to(&result, "1");
	while (pow)
	{
		copy_t_decimal(x, &current_value);
		current_power = 1;
		while (current_power * 2 <= pow)
		{
			square_positive_decimal(&current_value);
			current_power *= 2;
		}
		pow -= current_power;
		multiply_positive_decimal(&result, &current_value);
	}
	copy_t_decimal(&result, x);
}
