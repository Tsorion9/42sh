#include "libft.h"

char		*find_closing_bracket(char *s, char *not_quoted)
{
	while (*s)
	{
		if (*s == ']' && *not_quoted == 'y')
			break ;
		s++;
		not_quoted++;
	}
	return (s);
}

void		fill_subrange(char **start, char symbols[256], char **not_quoted)
{
	char min;
	char max;

	if (*(*start + 2) == ']' && *(*not_quoted + 2) == 'y')
	{
		symbols[(int)**start] = 1;
		symbols[(int)*(*start + 1)] = 1;
		*start += 2;
		*not_quoted += 2;
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
	*not_quoted += 3;
}

static void		init_local_variables(char symbols[256], int *negate_result)
{
	memset(symbols, 0, 256);
	*negate_result = 0;
}

static void		increment_2(char **pattern, char **not_quoted)
{
	(*pattern)++;
	(*not_quoted)++;
}

/*
** Return whether we should negate the range
*/
int				find_range(char *pattern, char *closing_bracket,
		char symbols[256], char *not_quoted)
{
	int negate_result;

	init_local_variables(symbols, &negate_result);
	if (!*closing_bracket)
	{
		symbols[(int)'['] = 1;
		return (negate_result);
	}
	increment_2(&pattern, &not_quoted);
	if (*pattern == '^')
	{
		negate_result = 1;
		increment_2(&pattern, &not_quoted);
	}
	while (pattern != closing_bracket)
	{
		if (*(pattern + 1) == '-' && *(not_quoted + 1) == 'y')
			fill_subrange(&pattern, symbols, &not_quoted);
		else
		{
			symbols[(int)*pattern] = 1;
			increment_2(&pattern, &not_quoted);
		}
	}
	return (negate_result);
}

void				negate(char arr[256])
{
	int i;

	i = 0;
	while (i < 256)
	{
		arr[i] = !(arr[i]);
		i++;
	}
}

/*
** Pattern starts with [
** in case of no closed ], match exactly [
** [asd] - any of a, s, d
** [^asd] - not a,s,d
** [a-zA-Z] - any of a-z or A-Z
*/
static int			range_match(char *string, char *pattern, char *not_quoted)
{
	char		*closing_bracket;
	static char	symbols[256];

	closing_bracket = find_closing_bracket(pattern, not_quoted);
	if (find_range(pattern, closing_bracket, symbols, not_quoted) == 1)
	{
		negate(symbols);
	}
	if (symbols[(int)*string])
		return (ft_clever_match(string + 1,
				*closing_bracket ? closing_bracket + 1 : pattern + 1,
				*closing_bracket ?
				not_quoted + (closing_bracket - pattern) + 1 :
				not_quoted + 1));
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
** not_quoted - string with length equal to pattern
** that containg only letters 'y' and 'n'
** if pattern[i] is one of {*, ?, [, ], -}
** and not_quoted[i] == 'n', special meaning of pattern[i]
** is discarded
*/
int					ft_clever_match(char *string, char *pattern,
		char *not_quoted)
{
	if (!*string && !*pattern)
		return (1);
	if (*pattern == '*' && *not_quoted == 'y')
		return (ft_clever_match(string, pattern + 1, not_quoted + 1) ||
				(*string ? ft_clever_match(string + 1,
				pattern, not_quoted) : 0));
	else if (*pattern == '?' && *not_quoted == 'y')
		return (*string ? ft_clever_match(string + 1,
					pattern + 1, not_quoted + 1) : 0);
	else if (*pattern == '[' && *not_quoted == 'y')
		return (range_match(string, pattern, not_quoted));
	else if (*pattern != *string)
		return (0);
	return (ft_clever_match(string + 1, pattern + 1, not_quoted + 1));
}

