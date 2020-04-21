/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:53:27 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "fp_type.h"

int				is_usgn(t_spec spec)
{
	if (\
			spec.conv == 'u' || \
			spec.conv == 'p' || \
			spec.conv == 'o' || \
			spec.conv == 'x' || \
			spec.conv == 'X')
		return (1);
	return (0);
}

void			*extr_sint(t_spec spec, va_list *vl, long long *p)
{
	if (spec.length == ll)
		*p += va_arg(*vl, long long);
	else if (spec.length == l)
		*p += va_arg(*vl, long);
	else if (spec.length == h)
		*p += (short)va_arg(*vl, int);
	else if (spec.length == hh)
		*p += (char)va_arg(*vl, int);
	else
		*p += va_arg(*vl, int);
	return ((void *)p);
}

/*
** 		// pointer is actually an unsigned long in 64bit systems
*/

void			*extr_uint(t_spec spec, va_list *vl, long long *p)
{
	if (spec.length == ll)
		*p += va_arg(*vl, unsigned long long);
	else if (spec.length == l || spec.conv == 'p')
		*p += va_arg(*vl, unsigned long);
	else if (spec.length == h)
		*p += (unsigned short)va_arg(*vl, unsigned int);
	else if (spec.length == hh)
		*p += (unsigned char)va_arg(*vl, unsigned int);
	else
		*p += va_arg(*vl, unsigned int);
	return ((void *)p);
}

/*
**	Choose integer extractor depending on signed/unsigned
*/

t_i_extr_fun	choose_i_extr(t_spec spec)
{
	return (is_usgn(spec) ? &extr_uint : &extr_sint);
}
