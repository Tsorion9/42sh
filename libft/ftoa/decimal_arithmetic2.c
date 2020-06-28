/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decimal_arithmetic2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 04:01:11 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 04:01:14 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fp.h"

/*
**Conversion functions below
*/

void		insert_point(int after_dot, char *s)
{
	while (*s)
		s++;
	if (after_dot == 0)
	{
		*s++ = '.';
		*s++ = '0';
		*s = 0;
		return ;
	}
	while (after_dot)
	{
		*(s + 1) = *s;
		after_dot--;
		s--;
	}
	*(s + 1) = *s;
	*s = '.';
}

int			to_ascii(t_decimal repr, char *s)
{
	int		i;
	int		n_digits;

	i = 0;
	if (repr.is_negative)
		s[i++] = '-';
	n_digits = repr.end - repr.start + 1;
	if (n_digits == repr.after_dot)
		s[i++] = '0';
	while (n_digits)
	{
		s[i++] = *(repr.start++) + '0';
		n_digits--;
	}
	s[i] = 0;
	insert_point(repr.after_dot, s);
	return (i);
}

int			nchar_after_dot(char *s)
{
	int	n;

	n = 0;
	while (*s != '.' && *s)
		s++;
	if (*s)
		s++;
	while (*s++)
		n++;
	return (n);
}

int			ndigits(char *s)
{
	int	n_digits;
	int	len;

	len = -1;
	n_digits = 0;
	while (s[++len])
	{
		if (s[len] >= '0' && s[len] <= '9')
			n_digits++;
	}
	return (n_digits);
}

void		copy_digits_numbers(char *src, char *dst)
{
	while (*src)
	{
		if (*src >= '0' && *src <= '9')
		{
			*dst = *src - '0';
			dst++;
		}
		src++;
	}
}
