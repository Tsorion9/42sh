#include "expansions.h"

void	remove_backslash(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	if ((*str)[*i] != '\0')
	{
		(*str)[*rep] = (*str)[*i];
		(*i)++;
		(*rep)++;
	}
}

void	remove_quote(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	while ((*str)[*i] != '\0' && (*str)[*i] != '\'')
	{
		(*str)[*rep] = (*str)[*i];
		(*i)++;
		(*rep)++;
	}
	if ((*str)[*i] == '\'')
		(*i)++;
}

int		dquote_spec(char c)
{
	if (c == '$' || c == '`' || c == '\\' || c == '\n' || c == '"')
		return (1);
	return (0);
}

void	remove_dquote(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	while ((*str)[*i] != '\0' && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '\\' && dquote_spec((*str)[*i + 1]))
			remove_backslash(str, i, rep);
		else
		{
			(*str)[*rep] = (*str)[*i];
			(*i)++;
			(*rep)++;
		}
	}
	if ((*str)[*i] == '"')
		(*i)++;
}

void	quote_removal(char **str)
{
	size_t i;
	size_t rep;

	i = 0;
	rep = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
			remove_backslash(str, &i, &rep);
		else if ((*str)[i] == '\'')
			remove_quote(str, &i, &rep);
		else if ((*str)[i] == '"')
			remove_dquote(str, &i, &rep);
		else
		{
			(*str)[rep] = (*str)[i];
			i++;
			rep++;
		}
	}
	ft_bzero(&((*str)[rep]), i - rep);
}
