/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 14:55:10 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
**	Fill all fields of structure with zeros.
*/

void		init_spec(t_spec *spec)
{
	spec->flag_zero = 0;
	spec->flag_hash = 0;
	spec->flag_plus = 0;
	spec->flag_dash = 0;
	spec->flag_space = 0;
	spec->width = 0;
	spec->precision = -1;
	spec->length = 0;
	spec->conv = 0;
	spec->stupid_c0_special_case = 0;
}

void		read_flag(const char c, t_spec *spec)
{
	if (c == '+')
		spec->flag_plus = 1;
	if (c == '-')
		spec->flag_dash = 1;
	if (c == ' ')
		spec->flag_space = 1;
	if (c == '#')
		spec->flag_hash = 1;
	if (c == '0')
		spec->flag_zero = 1;
}

/*
**	Read any nonnegative number of flags.
**	One flag can be mentioned more than once
**  No other chars expected here.
**	Return a pointer to first non-flag char in f
*/

const char	*read_flags(const char *f, t_spec *spec)
{
	while (*f == '+' || *f == '-' || *f == ' ' || *f == '#' || *f == '0')
		read_flag(*(f++), spec);
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "width"
**	Return: ptr to first non-digit in f
*/

const char	*read_width(const char *f, t_spec *spec)
{
	if (ft_isdigit(*f))
		spec->width = ft_atoi(f);
	while (ft_isdigit(*f))
		f++;
	return (f);
}
