/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 16:59:23 by dpenney           #+#    #+#             */
/*   Updated: 2019/11/29 17:01:55 by dpenney          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Probably, 21 or 20, No problem here
*/

#define MAX_DIGITS 22

static int	our_abs(int n)
{
	return (n < 0 ? -1 * n : n);
}

/*
**	Fill string representation
*/

static void	fill(char *s, long long n, char *base, int sgn)
{
	int		b_len;
	int		pos;

	pos = 0;
	if (!n)
	{
		*s = base[0];
		return ;
	}
	b_len = ft_strlen(base);
	while (n)
	{
		if (sgn)
		{
			s[pos++] = base[our_abs(n % b_len)];
			n = n / b_len;
		}
		else
		{
			s[pos++] = base[our_abs((unsigned long long)n % b_len)];
			n = (unsigned long long)n / b_len;
		}
	}
	ft_strrev(s);
}

/*
**	Treat characters of base as digits and perform itoa
**	Cast n as unsigned if sgn == 0
**	Caller should provide a valid base
*/

char		*ft_itoa_base(long long n, char *base, int sgn)
{
	char	*s;

	if (!(s = ft_strnew(MAX_DIGITS)))
		return (0);
	fill((sgn && n < 0 && (*s = '-')) ? s + 1 : s, n, base, sgn);
	return (s);
}
