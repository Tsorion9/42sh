/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:03:10 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "fp_type.h"

/*
**	If we understand rules of C language correctly, :-) this conversions
**  do not lead to data corruption.
**	Now we may have UB (signed overflow).
*/

void	*int_extractor(t_spec spec, va_list *vl)
{
	long long	*p;

	if ((p = ft_memalloc(sizeof(long long))))
		return (choose_i_extr(spec)(spec, vl, p));
	return ((void *)p);
}

/*
**  spec.length == ll || spec.length == l ||
*/

void	*float_extractor(t_spec spec, va_list *vl)
{
	long double	*p;

	if ((p = ft_memalloc(sizeof(long double))))
	{
		if (spec.length == L)
			*p += va_arg(*vl, long double);
		else
			*p += va_arg(*vl, double);
	}
	return ((void *)p);
}

void	*char_extractor(t_spec spec, va_list *vl)
{
	char	*p;

	(void)spec;
	if ((p = ft_memalloc(sizeof(char) * 2)))
	{
		p[0] = va_arg(*vl, int);
		p[1] = 0;
	}
	return ((void *)p);
}

/*
**  Single case where we do not allocate external memory
**	UB reproduction (small precision and NULL str)
*/

void	*str_extractor(t_spec spec, va_list *vl)
{
	char *arg;

	arg = va_arg(*vl, char *);
	(void)spec;
	if (!arg)
		arg = "(null)";
	return ((void *)arg);
}

/*
**  Do nothing. Really, just do nothing
**  Will be used for % conv specifier
*/

/*
** Probably, this can break portability to clang.
** Use void() typecasting then (void)spec
** Return value is nonzero and must not be used
*/

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void	*dummy_extractor(t_spec spec, va_list *vl)
{
	return ((void *)1);
}
#pragma GCC diagnostic pop
