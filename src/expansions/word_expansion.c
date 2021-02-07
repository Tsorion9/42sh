#include <unistd.h>
#include "expansions.h"
#include "environment.h"
#include "exec.h"

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

void 	try_tilde_expansion(char **src_word, size_t *i, int word_state, int inside_assignment_word)
{
	size_t	j;
	char 	c;
	int 	quoted_state;

	if ((word_state & IN_DQUOTE_STATE) || (word_state & IN_QUOTE_STATE))
		return ;
	if (*i == 0 || (inside_assignment_word &&
			(((*src_word)[*i - 1] == '=')  || (*src_word)[*i - 1] == ':')))	
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
		tilde_expansion(src_word, i, inside_assignment_word);
	}
	(*i)++; // skip '/' example: user_home/some_text '/' in the middle
	// would be skipped
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

int		expasnion_status(int status)
{
	static int g_status;

	if (status == GET_STATUS)
		return g_status;
	g_status = status;
	return g_status;
}

/*
** parameter[:]-[word]
*/

void	use_default_values(char **src_word, char **word,
						char *param_value, int have_colon)
{
	size_t	i;

	i = 0;
	if (have_colon)
	{
		word_expansion(word);
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
	else
	{
		if (param_value != NULL && !(*param_value))
		{
			ft_strdel(word);
			*word = ft_strnew(0);
			replace_value(src_word, *word, &i, ft_strlen(*src_word));
			free(*word);
			*word = NULL;
		}
		else if (param_value == NULL)
		{
			word_expansion(word);
			replace_value(src_word, *word, &i, ft_strlen(*src_word));
		}
	}
}

/*
** parameter[:]?[word]
*/

void	indicate_error_if_null_or_unset(char **src_word, char **word,
									 char *param, int have_colon)
{
	char	*param_value;

	param_value = ft_getenv(env, param);
	if (param_value != NULL && *param_value == '\0' && !have_colon)
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "42sh: %s: %s", param,
				   (**word == '\0') ? E_PARAM_NULL_OR_UNSET : *word);
		expasnion_status(EXPANSION_FAIL);
	}
}

/*
** parameter[:]+[word]
*/

void	use_alternative_value(char **src_word, char **word,
						   char *param_value, int have_colon)
{
	size_t	i;

	if (param_value == NULL || (have_colon && param_value == NULL))
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
	else
	{
		word_expansion(word);
		i = 0;
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
}

/*
** parameter[:]=[word]
*/

void	assign_default_values(char **src_word, char **word,
							  char *param, int have_colon)
{
	size_t	i;
	char	*param_value;

	i = 0;
	param_value = ft_getenv(env, param);
	if (param_value == NULL || (have_colon && param_value == NULL))
	{
		word_expansion(word);
		ft_setenv(env, param, *word);
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
	else
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
}

/*
** '-' == использовать значнение word после расширения
** '?' == выводит сообщение об ошибке, если значение unset/null
** '+' == использовать альтернативное значение
** '=' == присвоить значение
** '#' == удалить наименьший префикс
** '##' == удалить наибольший префикс
** '%' == удалить наименьший суффикс
** '%%' == удалить наибольший суффикс
**
** src_word исходное слово
** sep указатель на специальный параметр в src_word
** простыми словами, sep подстрока src_word, указывающая на спец символ
** parameter используется для присваивания значения, если необходимо
*/

void 	var_unset_or_empty(char **src_word, char **sep, char *param,
						 								int have_colon)
{
	char	c;
	char 	*word;

	c = **sep;
	word = ft_strdup(*sep + 1);
	if (c == '-')
		use_default_values(src_word, &word, ft_getenv(env, param), have_colon);
	else if (c == '?')
		indicate_error_if_null_or_unset(src_word, &word, param, have_colon);
	else if (c == '+')
		use_alternative_value(src_word, &word, ft_getenv(env, param),
						have_colon);
	else if (c == '=')
		assign_default_values(src_word, &word, param, have_colon);
	else if (c == '%' || c == '#')
	{
		ft_strdel(src_word);
		*src_word = ft_strnew(0);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "%s %s", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
	}
	free(word);
}

/*
** '-' == использовать значнение word после расширения
** '?' == выводит сообщение об ошибке, если значение unset/null
** '+' == использовать альтернативное значение
** '=' == присвоить значение
** '#' == удалить наименьший префикс
** '##' == удалить наибольший префикс
** '%' == удалить наименьший суффикс
** '%%' == удалить наибольший суффикс
**
** src_word исходное слово
** sep указатель на специальный параметр в src_word
** простыми словами, sep подстрока src_word, указывающая на спец символ
** parameter используется для присваивания значения, если необходимо
*/

void	var_not_null(char **src_word, char **sep, char *param)
{
	char	c;
	char 	*word;
	char 	*param_value;
	size_t	i;

	c = **sep;
	word = ft_strdup(*sep + 1);
	param_value = ft_getenv(env, param);
	i = 0;
	if (c == '-' || c == '=' || c == '?')
		replace_value(src_word, param_value, &i, ft_strlen(*src_word));
	else
	{
		ft_fprintf(STDERR_FILENO, "%s %s", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
	}
	free(word);
}

/*
** '{' src_word '}'
** src_word == parameter( [:][=+-?] | (#[#] | %[%]) )word
*/

void 	parameter_expansion(char **src_word)
{
	size_t	i;
	char	*sep;
	char 	*parameter;
	char 	*var_value;
	int		have_colon;

	i = 0;
	have_colon = 0;
	sep = ft_strchr(*src_word, ':');
	if (!sep)
		sep = ft_strchr_any(*src_word, "-=?+%#");
	if (sep)
	{
		parameter = ft_strsub(*src_word, 0, (size_t)(sep - *src_word));
		if (*parameter == '\0')
		{
			ft_fprintf(2, "42sh: %s: %s", *src_word, E_BAD_SUBSTITUTION);
			expasnion_status(EXPANSION_FAIL);
			return ;
		}
		var_value = ft_getenv(env, parameter);
		if (*sep == ':')
		{
			sep++;
			have_colon = 1;
		}
		if (!var_value || !(*var_value))
			var_unset_or_empty(src_word, &sep, parameter, have_colon);
		else
			var_not_null(src_word, &sep, parameter);
		free(parameter);
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

void 	last_cmd_status_expansion(char **src_word, size_t *i)
{
	char 	*s_status;
	int status;

	status = last_cmd_status;
	if (WIFEXITED(last_cmd_status))
		status = WEXITSTATUS(last_cmd_status);
	if (WIFSIGNALED(last_cmd_status))
		status = WTERMSIG(last_cmd_status) + 128;
	if (WIFSTOPPED(last_cmd_status))
		status = WSTOPSIG(last_cmd_status) + 128;

	s_status = ft_itoa(status);
	replace_value(src_word, s_status, i, 2);
	free(s_status);
}


/*
** perform variable (parameter) expansion.
**
** syntax           POSIX description   var defined     var undefined
** ======           =================   ===========     =============
** ${var}           Substitute          var             void
** ${var:-word}     Use Deflt Values    var             word
** ${var-word}      Use Deflt Values    var             void
** ${var:?message}  Error if NULL/Unset var             print message and exit shell,
**                                                      (if message is empty,print
**                                                      "var: parameter not set")
** ${#var}          Calculate String Length
*/

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
		if (s[0] == '#')
		{
			res = length_expansion(&s);
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
	{
		j = find_closing_brace(*src_word, *i + 1);
		s = ft_strsub(*src_word, *i + 2, j - *i - 2);
		command_substitution(&s);
		replace_value(src_word, s, i, j + 1);
		return ;
	}
	else if (c == '$')
		pid_expansion(src_word, i);
	else if (c == '?')
		last_cmd_status_expansion(src_word, i);
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
	int		inside_assignment_word;

	if ((*source_word) == NULL || !(**source_word))
		return (EXPANSION_EMPTY_WORD);
	expasnion_status(EXPANSION_SUCCESS);
	i = 0;
	word_state = 0;
	inside_assignment_word = 0;
	while ((*source_word)[i] && expasnion_status(GET_STATUS) != EXPANSION_FAIL)
	{
		if (word_state == 0 && (*source_word)[i] == '=') /* Not quotes */
			inside_assignment_word = 1;
		c = (*source_word)[i];
		if (c == '~')
			try_tilde_expansion(source_word, &i, word_state, inside_assignment_word);
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
	return (expasnion_status(GET_STATUS));
}
