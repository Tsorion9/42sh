#include "environment.h"
#include "static_env.h"
#include "str_replace.h"

static int			expand_special_parameter(char **word, int *pos)
{
	(void)word;
	(void)pos;
	ft_fprintf(2, "%s\n", "Warning: Special parameters not implemented!");
	return (0);
}

static int			expand_positional_parameter(char **word, int *pos)
{
	(void)word;
	(void)pos;
	ft_fprintf(2, "%s\n", "Warning: Positional parameters not implemented!");
	return (0);
}

static int			is_special_parameter(char c)
{
	if (c == '@' || c == '*' || c == '?' || c || '-' || c == '$' || c == '!')
		return (0);
}

static int is_valid_namechar(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static char	*get_varname(char *word, int pos)
{
	int		len;
	char	*name;

	len = 0;
	while (is_valid_namechar(word[pos + 1 + len]))
		len++;
	if (!len)
		return (NULL);
	name = malloc(len + 1);
	ft_strncpy(name, word + pos + 1, len);
	name[len] = 0;
	return (name);
}

int			expand_dollar(char **word, int *pos)
{
	char	*varname;
	char	*value;

	if (!(*word)[*pos + 1])
		return (0);
	else if (is_special_parameter((*word)[*pos + 1]))
		return (expand_special_parameter(word, pos));
	else if (ft_isdigit((*word)[*pos + 1]))
		return (expand_positional_parameter(word, pos));
	else if ((varname = get_varname(*word, *pos)))
	{
		if(!(value = ft_getenv(static_env_action(get, NULL), varname)))
		{
			*pos += ft_strlen(varname); // UNSPECIFIED BY POSIX. We ignore expansions, bash expands to emptystring
			free(varname);
			return (0);
		}
		str_repl_inplace(word, *pos, *pos + ft_strlen(varname), value);
		*pos += ft_strlen(value);
		free(varname);
	}
	else
	{
		/* Behaviour is unspeified! */
		return (0);
	}
	return (0);
}
