/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 18:30:09 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "apply_spec.h"

/*
** 	here dot is always in number if this function is called
*/

char	*float_precision(char *s, t_spec spec)
{
	int		precision;
	int		nchar_after_dot;
	char	*suffix;

	precision = spec.precision;
	nchar_after_dot = len_after_dot(s);
	if (precision > nchar_after_dot)
	{
		if (nchar_after_dot == 0 &&
			!(s = add_suffix(s, ".")))
			return (0);
		suffix = char_n_dup('0', precision - nchar_after_dot);
		return (add_suffix(s, suffix));
	}
	if (precision < nchar_after_dot)
		s = round_float(s, precision);
	if (precision == 0 && spec.flag_hash)
		s = add_suffix(s, ".");
	return (s);
}

/*
**	< 0 => uninitialized
**	for floats default is 6
*/

/*
**	Insert zeros from the left to nonfloat numeric (after - if negative)
**	PRINT NOTHING IN THAT CASE
*/

char	*apply_precision(char *s, t_spec spec)
{
	char	*zeros;

	if (spec.precision < 0 && spec.conv == 'f')
		spec.precision = DEFAULT_FLOAT_PRECISION;
	if (spec.precision < 0)
		return (s);
	if (spec.conv == 's')
	{
		s[spec.precision] = 0;
		return (s);
	}
	if (spec.conv == 'f')
		return (float_precision(s, spec));
	if (spec.precision == 0 && !ft_strcmp(s, "0"))
		return (str_replace(s, '0', 0));
	if (spec.precision > 0 && is_nonfloat_numeric(spec))
	{
		zeros = char_n_dup('0', spec.precision - ft_strlen(s) + (*s == '-'));
		return (str_insert(s, zeros, (*s == '-') ? 1 : 0));
	}
	return (s);
}

/*
**	Apply flag zero to different cases
*/

char	*apply_fzero(char *s, t_spec spec)
{
	int		nzeros;
	char	*zeros;

	nzeros = spec.width - ft_strlen(s);
	if (nzeros <= 0 || (!is_numeric(spec) && spec.conv != '%'))
		return (s);
	zeros = char_n_dup('0', nzeros);
	if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
		return (str_insert(s, zeros, 2));
	if (s[0] == '-' || s[0] == '+' || spec.flag_space == 1)
		return (str_insert(s, zeros, 1));
	return (str_insert(s, zeros, 0));
}

char	*apply_fdash(char *s, t_spec spec)
{
	char	*spaces;
	int		len;

	len = ft_strlen(s);
	if (len >= spec.width)
		return (s);
	spaces = char_n_dup(' ', spec.width - len);
	return (spec.flag_dash ? add_suffix_free(s, spaces) \
				: add_prefix_free(s, spaces));
}

/*
** Width and flags '0' and '-' are logically tied
*/

char	*apply_width(char *s, t_spec spec)
{
	if (spec.flag_zero == 1 && (spec.precision <= 0 || spec.conv == 'f') \
			&& !spec.flag_dash)
		return (apply_fzero(s, spec));
	if (spec.flag_zero == 1 && spec.conv == '%' && !spec.flag_dash)
		return (apply_fzero(s, spec));
	return (apply_fdash(s, spec));
}
