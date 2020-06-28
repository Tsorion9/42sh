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

int			is_signed_conversion(t_spec spec)
{
	if (spec.conv == 'i' || spec.conv == 'f' || spec.conv == 'd')
		return (1);
	return (0);
}

int			is_numeric(t_spec spec)
{
	if (\
		spec.conv == 'd' || spec.conv == 'i' || \
		spec.conv == 'o' || spec.conv == 'u' || \
		spec.conv == 'x' || spec.conv == 'X' || \
		spec.conv == 'f')
		return (1);
	return (0);
}

int			is_nonfloat_numeric(t_spec spec)
{
	if (is_numeric(spec) || spec.conv != 'f')
		return (1);
	return (0);
}

/*
** return initial string
*/

char		*str_replace(char *s, char pattern, char replacement)
{
	char	*start;

	start = s;
	while (*s)
	{
		if (*s == pattern)
			*s = replacement;
		s++;
	}
	return (start);
}

/*
**  Warning!
**  s is always freed. suffix is always not freed
**	In case of NULL argument return NULL
*/

char		*add_suffix(char *s, char *suffix)
{
	int		len;
	char	*new;

	if (!s || !suffix)
	{
		free(s);
		return (0);
	}
	len = ft_strlen(s);
	new = ft_strnew(len + ft_strlen(suffix));
	if (!new)
	{
		free(s);
		return (0);
	}
	ft_strcpy(new, s);
	ft_strcpy(new + len, suffix);
	free(s);
	return (new);
}
