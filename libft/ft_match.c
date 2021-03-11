/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:51:21 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 14:51:22 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "clever_match_misc.h"

static char		*find_closing_bracket(char *s)
{
	while (*s)
	{
		if (*s == ']')
			break ;
		s++;
	}
	return (s);
}

static void		fill_subrange(char **start, char symbols[256])
{
	char min;
	char max;

	if (*(*start + 2) == ']')
	{
		symbols[(int)**start] = 1;
		symbols[(int)*(*start + 1)] = 1;
		*start += 2;
		return ;
	}
	min = **start > *(*start + 2) ? *(*start + 2) : **start;
	max = **start < *(*start + 2) ? *(*start + 2) : **start;
	while (min <= max)
	{
		symbols[(int)min] = 1;
		min++;
	}
	*start += 3;
}

/*
** Return whether we should negate the range
*/

static int			find_range(char *pattern, char *closing_bracket,
		char symbols[256])
{
	int negate_result;

	init_local_variables(symbols, &negate_result);
	if (!*closing_bracket)
	{
		symbols[(int)'['] = 1;
		return (negate_result);
	}
	pattern++;
	if (*pattern == '^')
	{
		negate_result = 1;
		pattern++;
	}
	while (pattern != closing_bracket)
	{
		if (*(pattern + 1) == '-')
			fill_subrange(&pattern, symbols);
		else
		{
			symbols[(int)*pattern] = 1;
			pattern++;
		}
	}
	return (negate_result);
}

/*
** Pattern starts with [
** in case of no closed ], match exactly [
** [asd] - any of a, s, d
** [^asd] - not a,s,d
** [a-zA-Z] - any of a-z or A-Z
*/

int					range_match(char *string, char *pattern)
{
	char		*closing_bracket;
	static char	symbols[256];

	closing_bracket = find_closing_bracket(pattern);
	if (find_range(pattern, closing_bracket, symbols) == 1)
	{
		negate(symbols);
	}
	if (symbols[(int)*string])
	{
		return (ft_match(string + 1,
				*closing_bracket ? closing_bracket + 1 : pattern + 1));
	}
	return (0);
}

/*
** Supported syntax:
** * - any string
** ? - any char
** [asd] - any of a, s, d
** [^asd] - not a,s,d
** [a-zA-Z] - any of a-z or A-Z
**
** Warning: quoting not supported!!
*/

int					ft_match(char *string, char *pattern)
{
	if (!*string && !*pattern)
		return (1);
	if (*pattern == '*')
		return (ft_match(string, pattern + 1) ||
				(*string ? ft_match(string + 1, pattern) : 0));
	else if (*pattern == '?')
		return (*string ? ft_match(string + 1, pattern + 1) : 0);
	else if (*pattern == '[')
		return (range_match(string, pattern));
	else if (*pattern != *string)
		return (0);
	return (ft_match(string + 1, pattern + 1));
}
