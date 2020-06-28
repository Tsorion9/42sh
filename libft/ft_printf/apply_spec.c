/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_spec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpenney <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:55:09 by dpenney           #+#    #+#             */
/*   Updated: 2019/12/05 03:30:50 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include "apply_spec.h"

char		*add_suffix_free(char *s, char *suffix)
{
	char	*c;

	c = add_suffix(s, suffix);
	free(suffix);
	return (c);
}

char		*add_prefix_free(char *s, char *prefix)
{
	char	*c;

	c = add_prefix(s, prefix);
	free(prefix);
	return (c);
}

/*
**  Return string that contains n chars c
**	If n <= 0, return nonzero ptr to empty string
*/

char		*char_n_dup(char c, int n)
{
	char	*res;

	res = 0;
	if (n < 0)
		n = 0;
	if (n + 1 < n)
		return (0);
	res = ft_memalloc(n > 0 ? n + 1 : 1);
	if (!res)
		return (0);
	if (n <= 0)
		return (res);
	while (n--)
		res[n] = c;
	return (res);
}

/*
**  Modify only the copy of original string
**	Always return a copy. Copy always MUST be freed.
*/

char		*apply_spec(char *s, t_spec *spec)
{
	char	*new;

	if (\
		!(new = ft_strdup(s)) || \
		!(new = apply_precision(new, *spec)) || \
		!(new = apply_numeric_flags(new, *spec)) || \
		!(new = apply_width(new, *spec)))
		return (0);
	if (ft_strlen(s) == 0 && spec->conv == 'c')
	{
		spec->stupid_c0_special_case = 1;
	}
	if (spec->conv != 's' && spec->conv != 'f')
		free(s);
	return (new);
}
