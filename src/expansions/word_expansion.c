#include "expansions.h"
#include "environment.h"

/*
** На вход ожидает получить строку с кавычкой в первом символе
** Пример:	'someword'more
** 			"someword"more
*/
size_t	find_closing_quote(char *data)
{
	char	quote;

	quote = data[0];
	if (quote != '\'' && quote != '"')
		return (0);
	size_t	i;
	size_t	len;

	len = strlen(data);
	i = 0;
	while(++i < len)
	{
		if(data[i] == quote)
		{
			if(data[i-1] == '\\')
			{
				if(quote != '\'')
					continue;
			}
			return (i);
		}
	}
	return (0);
}

void 	try_tilde_expansion(char **src_word, size_t *i, int word_state)
{
	size_t	j;
	char 	c;
	int 	quoted_state;

	if ((word_state & IN_DQUOTE_STATE) || (word_state & IN_QUOTE_STATE))
		return ;
	if (*i == 0)
	{
		j = 0;
		quoted_state = 0;
		while ((*src_word)[j] != '\0' && quoted_state == 0)
		{
			c = (*src_word)[j];
			if (c == '\\')
			{
				quoted_state = 1;
				j++;
			}
			else if (c == '\'' || c == '"')
			{
				quoted_state = 1;
				j += find_closing_quote(*src_word + j);
			}
			else if (c == '/')
				break ;
			j++;
		}
		if (quoted_state)
		{
			*i = j;
			return ;
		}
		tilde_expansion(src_word, i);
	}
}

int 	is_valid_var_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (VALID_VAR_CHAR);
	return (INVALID_VAR_CHAR);
}

void 	var_expansion(char **src_word, size_t *i)
{
	size_t	j;
	char	*var_value;
	char 	*var_name;

	j = *i + 1; // skip '$'
	while ((*src_word)[j] && is_valid_var_char((*src_word)[j]))
		j++;
	var_name = ft_strsub(*src_word, *i + 1, j - *i - 1);
	var_value = ft_getenv(env, var_name);
	replace_value(src_word, var_value, i, j - *i);
	free(var_name);
}

void 	dollar_expansion(char **src_word, size_t *i, int *word_state)
{
	char	c;

	c = (*src_word)[*i + 1];
	if (c == '{')
		return ;
	else if (c == '(')
		return ;
	else if (is_valid_var_char(c))
		var_expansion(src_word, i);
}

int		word_expansion(char **source_word)
{
	size_t 	i;
	char 	c;
	int 	word_state;

	if ((*source_word) == NULL || !(**source_word))
		return (EXPANSION_EMPTY_WORD);
	i = 0;
	word_state = 0;
	while ((*source_word)[i])
	{
		c = (*source_word)[i];
		if (c == '~')
			try_tilde_expansion(source_word, &i, word_state);
		else if (c == '\\')
			i++;
		else if (c == '"')
			word_state |= IN_DQUOTE_STATE;
		else if (c == '\'')
		{
			if (!(word_state & IN_DQUOTE_STATE))
				i += find_closing_quote(*source_word + i);
		}
		else if (c == '$')
			dollar_expansion(source_word, &i, &word_state);
		i++;
	}
	return (1);
}