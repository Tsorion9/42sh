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
	size_t	i;
	size_t	len;

	quote = data[0];
	if (quote != '\'' && quote != '"')
		return (0);
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
		(*i)++; // skip '/' example: user_home/some_text '/' in the middle
		// would be skipped
	}
}

int 	is_valid_var_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (VALID_VAR_CHAR);
	return (INVALID_VAR_CHAR);
}

void 	var_expansion(char **src_word, size_t *i, int skeep_char)
{
	size_t	j;
	char	*var_value;
	char 	*var_name;

	j = *i + skeep_char; // skip '$' or '#'
	while ((*src_word)[j] && is_valid_var_char((*src_word)[j]))
		j++;
	var_name = ft_strsub(*src_word, *i + skeep_char, j - *i - skeep_char);
	var_value = ft_getenv(env, var_name);
	replace_value(src_word, var_value, i, j - *i);
	free(var_name);
}

/*
** Ожидается строка с балансом строк
*/
size_t	find_closing_brace(char *src_word, size_t i)
{
	char	o_brace;
	char	c_brace;
	char	c;
	int 	opens;

	o_brace = src_word[i];
	c_brace = o_brace == '{' ? '}' : ')';
	opens = 1;
	while (opens && ++i)
	{
		c = src_word[i];
		if ((c == '"' || c == '\'') && src_word[i - 1] != '\\')
			i += find_closing_quote(src_word + i);
		if (src_word[i - 1] != '\\')
		{
			if (c == o_brace)
				opens++;
			else if (c == c_brace)
				opens--;
		}
	}
	return (i);
}

int 	is_contain_any_spec(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_strchr("-=?+%#:'\"`!@$%^,.&*;()\\|~", s[i]) != NULL)
			return (1);
		i++;
	}
	return (0);
}

/*
** '{' #src_word '}'
** return NULL if error occured
** else malloced string of len of var
*/
char	*length_expansion(char **src_word)
{
	size_t	j;
	char 	*s_len;
	int 	len;

	j = 0;
	if (is_contain_any_spec((*src_word) + 1))
	{
		shell_err(E_BAD_SUBSTITUTION, *src_word);
		return (NULL);
	}
	var_expansion(src_word, &j, 1);
	len = ft_strlen(*src_word);
	s_len = ft_itoa(len);
	return (s_len);
}

char	*ft_strchr_any(char *s, char *search)
{
	int		i;
	char	*res;

	i = 0;
	while (search[i])
	{
		res = ft_strchr(s, search[i]);
		if (res)
			return (res);
		i++;
	}
	return (NULL);
}

// TODO
void 	parameter_action()
{

}

/*
** '{' src_word '}'
*/

void 	parameter_expansion(char **src_word)
{
	size_t	i;
	char	*sep;
	char 	*parameter;
	char 	*word;

	i = 0;
	sep = ft_strchr(*src_word, ':');
	if (!sep)
		sep = ft_strchr_any(*src_word, "-=?+%#");
	if (sep)
	{
		parameter = ft_strsub(*src_word, 0, (size_t)(sep - *src_word));
//		ft_printf("parameter =  %s\n", parameter);
	}
	else
		var_expansion(src_word, &i, 0);
}

/*
** The getpid() function are always successful, and no return
** value is reserved to indicate an error.
*/

void 	pid_expansion(char **src_word, size_t *i)
{
	int		pid;
	char 	*s_pid;

	pid = getpid();
	s_pid = ft_itoa(pid);
	replace_value(src_word, s_pid, i, 2);
	free(s_pid);
}

void 	dollar_expansion(char **src_word, size_t *i, int *word_state)
{
	char	c;
	char 	*s;
	char 	*res;
	size_t	j;

	c = (*src_word)[*i + 1];
	if (c == '{')
	{
		j = find_closing_brace(*src_word, *i + 1);
		s = ft_strsub(*src_word, *i + 2, j - *i - 2);
//		ft_printf("{ %s }\n", s);
		if (s[0] == '#')
		{
			res = length_expansion(&s);
//			ft_printf("res expansion = %s\n", res);
			replace_value(src_word, res, i, j + 1);
		}
		else
		{
			parameter_expansion(&s);
			replace_value(src_word, s, i, j + 1);
			free(s);
		}
	}
	else if (c == '(')
		return ;
	else if (c == '$')
		pid_expansion(src_word, i);
	else if (is_valid_var_char(c))
		var_expansion(src_word, i, 1);
	else
		(*i)++;
}

/*
** source_word malloced
*/

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
		{
			word_state ^= IN_DQUOTE_STATE;
			i++;
		}
		else if (c == '\'')
		{
			if (!(word_state & IN_DQUOTE_STATE))
				i += find_closing_quote(*source_word + i) + 1;
		}
		else if (c == '$')
			dollar_expansion(source_word, &i, &word_state);
		else
			i++;
	}
	return (1);
}