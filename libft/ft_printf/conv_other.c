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

/*
**	Here you can find declarations of non-integer conversion functions
*/

#include "printf.h"

/*
**   Char to string
*/

char	*ctoa(char c)
{
	char	*res;

	res = (char *)xmalloc(sizeof(char) * (1 + 1));
	if (!res)
		return (res);
	res[0] = c;
	res[1] = 0;
	return (res);
}

/*
** ID function =)
*/

char	*stoa(char *s)
{
	return (s);
}

/*
** Rerurn string representation of void ptr as hex
*/

char	*ptoa(void *p)
{
	return (itoa_bx(*(long long *)p));
}

char	*percent_to_a(void)
{
	return (ft_strdup("%"));
}
