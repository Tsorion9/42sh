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
#include "read_spec.h"

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "precision"
**	Return: ptr to first non-digit in f
*/

const char	*read_precision(const char *f, t_spec *spec)
{
	if (ft_isdigit(*f))
		spec->precision = ft_atoi(f);
	while (ft_isdigit(*f))
		f++;
	return (f);
}

/*
**	Skip all digits if they exist in format spec.
**  Fill the field "length"
**	Return: ptr to first non-length specifier in f
**	UPD: peers say, that we must process multiple length specifiers
**	and select max of them. Enum is ordered actually.
*/

const char	*read_length(const char *f, t_spec *spec)
{
	while (*f == 'l' || *f == 'L' || *f == 'h')
	{
		if (*f == 'l' && *(f + 1) == 'l' && spec->length < ll)
			spec->length = ll;
		if (*f == 'l' && *(f - 1) != 'l' && *(f + 1) != 'l' && spec->length < l)
			spec->length = l;
		if (*f == 'h' && *(f + 1) == 'h' && spec->length < hh)
			spec->length = hh;
		if (*f == 'h' && *(f - 1) != 'h' && *(f + 1) != 'h' && spec->length < h)
			spec->length = h;
		if (*f == 'L' && spec->length < L)
			spec->length = L;
		f++;
	}
	return (f);
}

const char	*read_conv_spec(const char *f, t_spec *spec)
{
	if (\
			*f != 'd' && *f != 'i' && *f != 'o' && *f != 'u' && *f != 'x' \
			&& *f != 'X' && *f != 'f' && *f != 'c' && *f != 's' && *f != 'p' \
			&& *f != '%')
		return (0);
	spec->conv = *f;
	return (++f);
}

/*
**	Read all arguments of conversion spceification
**	Return
**	-pointer to first char after the end of conversion specification
**	-0 in case of any problems (abscence of conversion specifier)
**	Side effects: change a spec
**	Copy of original UB (No precision spec provided but point exists)
**	Initialize with zero instead of negative number in this case
*/

const char	*read_spec(const char *format, t_spec *spec)
{
	init_spec(spec);
	format = read_flags(format, spec);
	format = read_width(format, spec);
	if (*format == '.')
	{
		spec->precision = 0;
		format = read_precision(++format, spec);
	}
	format = read_length(format, spec);
	format = read_conv_spec(format, spec);
	return (format);
}
