#include "environment.h"

static char	*replace(char **word, char *pos, const char *value)
{
	char	*new;
	char	*current;
	char	*tmp;

	new = malloc(pos - *word + ft_strlen(value) + 1);
	if (!new)
	{
		free(*word);
		*word = NULL;
		return (NULL);
	}
	current = new;
	tmp = *word;
	while (tmp < pos)
	{
		*current = *tmp;
		tmp++;
		current++;
	}
	ft_strcpy(current, value);
	free(*word);
	*word = new;
	return (new);
}

/*
** Actually, it must be much more complicated:
** https://pubs.opengroup.org/onlinepubs/9699919799/
**
** In this project we implement only the most simple variable name expansion.
** Others will be implemented in later projects
** (Upd: even more simple - $word$word will not be recognized as valval)
** Because variable names can contain $, which is quite stupid
*/

char	*expand_dollar(char **word, t_env env)
{
	char	*tmp;
	char	*value;

	value = NULL;
	tmp = *word;
	while (*tmp)
	{
		if (*tmp == '$' && *(tmp + 1))
		{
			value = ft_getenv(env, tmp + 1);
			break ;
		}
		tmp++;
	}
	if (value == NULL)
	{
		*tmp = 0;
		return (*word);
	}
	else
		return (replace(word, tmp, value));
}
