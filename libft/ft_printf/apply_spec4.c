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
**  Warning!
**  s is always freed. prefix is always not freed
**	In case of NULL argument return NULL
*/

char	*add_prefix(char *s, char *prefix)
{
	int		len;
	char	*new;

	if (!s || !prefix)
	{
		free(s);
		return (0);
	}
	len = ft_strlen(prefix);
	new = ft_strnew(len + ft_strlen(s));
	if (!new)
	{
		free(s);
		return (0);
	}
	ft_strcpy(new, prefix);
	ft_strcpy(new + len, s);
	free(s);
	return (new);
}

char	*prepend_zeros(char *s, int n)
{
	char	*prefix;

	if (!(prefix = char_n_dup('0', n)))
		return (0);
	s = add_prefix(s, prefix);
	free(prefix);
	return (s);
}

/*
**	Insert string src into n-th position of string dst
**	free src and dst
*/

char	*str_insert(char *dst, char *src, int pos)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strnew(ft_strlen(src) + ft_strlen(dst));
	if (!new)
		return (0);
	while (i < pos)
	{
		new[i] = dst[i];
		i++;
	}
	ft_strcat(new, src);
	ft_strcat(new, dst + i);
	free(src);
	free(dst);
	return (new);
}

int		only_zeros(char *s)
{
	while (*s)
		if (*s++ != '0')
			return (0);
	return (1);
}

char	*apply_hash(char *s, t_spec spec)
{
	if (((spec.conv == 'p') && ft_strcmp(s, "(nil)")))
		return (add_prefix(s, "0x"));
	if (spec.flag_hash == 1 && spec.precision == 0 && spec.conv == 'o')
		return (add_prefix(s, "0"));
	if (spec.flag_hash != 1 || only_zeros(s))
		return (s);
	if (spec.conv == 'o' && s[0] != '0')
		return (add_prefix(s, "0"));
	if (\
			(spec.conv == 'x' && ft_strcmp(s, "0")) ||\
			((spec.conv == 'p') && ft_strcmp(s, "(nil)")))
		return (add_prefix(s, "0x"));
	if (spec.conv == 'X' && ft_strcmp(s, "0"))
		return (add_prefix(s, "0X"));
	if (spec.conv == 'f' && !ft_strchr(s, '.'))
		return (add_suffix(s, ".0"));
	return (s);
}
