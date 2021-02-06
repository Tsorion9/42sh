#include "libft.h"

static int	contains_unquoted_eq(const char *s)
{
	int	squote;
	int	dquote;

	squote = 0;
	dquote = 0;
	while (*s)
	{
		if (*s == '=' && !squote && !dquote)
			return (1);
		if (*s == '\\' && (!*(++s) || !*(++s)))
			break ;
		if (*s == '\'' && !dquote)
			squote = squote ? 0 : 1;
		if (*s == '\"' && !squote)
			dquote = dquote ? 0 : 1;
		s++;
	}
	return (0);
}

static int	varname_looks_ok(const char *s)
{
	if (*s == '=' || ft_isdigit(*s))
		return (0);
	while (*s)
	{
		if (*s == '=')
			return (1);
		if (*s == '\\' || *s == '\"' || *s == '\'')
			return (0);
		s++;
	}
	return (0);
}

/*
** assignment word is a word that contains unquoted '='
** not in the first position and contains no "\'", '"', or "\\" before '='
*/

int			looks_like_assignment_word(const char *s)
{
	if (contains_unquoted_eq(s) && varname_looks_ok(s))
		return (1);
	return (0);
}
