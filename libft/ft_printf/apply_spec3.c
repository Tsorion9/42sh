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
#include "apply_spec.h"

/*
** Man page says sign should always be + or -. How about 0??
*/

char	*apply_plus(char *s, t_spec spec)
{
	if (spec.flag_plus != 1)
		return (s);
	if (is_signed_conversion(spec) && s[0] != '-')
		return (add_prefix(s, "+"));
	return (s);
}

/*
** Man page says prefix should be added only for POSITIVE numbers
** We reproduce bug and consider 0 as positive number
*/

char	*apply_space(char *s, t_spec spec)
{
	if (spec.flag_space != 1 || spec.flag_plus == 1)
		return (s);
	if (is_signed_conversion(spec) && s[0] != '-')
		return (add_prefix(s, " "));
	return (s);
}

/*
**	Return number of chars in string after dot
**	or 0 if no dot in char
*/

int		len_after_dot(char *s)
{
	while (*s && *s != '.')
		s++;
	return (*s ? ft_strlen(++s) : 0);
}

char	*last_check(int carry_bit, char *digit, char *s, int precision)
{
	if (carry_bit && digit == s)
		s = str_insert(s, ft_strdup("1"), ft_isdigit(*s) ? 0 : 1);
	if (precision == 0)
		return (str_replace(s, '.', 0));
	return (s);
}

/*
**  Caller must provide a precision > than number of chars after dot
*/

char	*round_float(char *s, int precision)
{
	int		carry_bit;
	char	*digit;

	carry_bit = 0;
	digit = ft_strchr(s, '.') + precision + 1;
	if (*digit >= '5')
		carry_bit++;
	*digit = 0;
	while (carry_bit && digit != s)
	{
		digit--;
		if (*digit == '+' || *digit == '-' || *digit == '.')
			continue;
		if (*digit == '9')
		{
			carry_bit = 1;
			*digit = '0';
		}
		else
		{
			(*digit)++;
			carry_bit = 0;
		}
	}
	return (last_check(carry_bit, digit, s, precision));
}
