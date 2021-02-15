#include <unistd.h>
#include "expansions.h"
#include "environment.h"
#include "readline.h"

// TODO Используется в нескольких функциях
int 	is_valid_var_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (VALID_VAR_CHAR);
	return (INVALID_VAR_CHAR);
}

int		expasnion_status(int status)
{
	static int g_status;

	if (status == GET_STATUS)
		return g_status;
	g_status = status;
	return g_status;
}

static void			init_history_num_and_first(t_history **history_first,
	int *number_of_history)
{
	t_history *history;

	history = rp(NULL)->history;
	while (history->prev)
		history = history->prev;
	*number_of_history = 0;
	while (history->next)
	{
		history = history->next;
		(*number_of_history)++;
	}
	*history_first = history;
	(*number_of_history)--;
}

static t_history	*get_history(t_history *history_first,
	const int number_of_history, int history_number)
{
	t_history *history;

	if (history_number > number_of_history)
		history_number = number_of_history - 1;
	if (history_number < 0)
	{
		history_number = number_of_history + history_number;
		if (history_number < 1)
			history_number = 1;
	}
	history = history_first;
	while (history->prev && history_number)
	{
		history = history->prev;
		history_number--;
	}
	return (history);
}

static int			search_str_in_history(const char *str)
{
	t_history	*history;
	int			found;
	int			history_number;

	history_number = 0;
	history = rp(NULL)->history;
	while (history->prev)
		history = history->prev;
	found = 0;
	while (history && !found && history_number < HISTSIZE)
	{
		if (ft_strfirststr(history->str, str))
			found = 1;
		history = history->next;
		history_number++;
	}
	return ((history_number - 2) * (-1));
}

static int			search_history_number(char *str)
{
	if (str)
	{
		if (ft_isnumber(str))
			return (ft_atoi(str));
		else if (str[0] != '-')
			return (search_str_in_history(str));
	}
	return (-1);
}

static size_t		find_end_history_expansions(const char *str)
{
	size_t	len;

	len = 0;
	while (ft_isalpha(*str) || *str == '-' || ft_isdigit(*str))
	{
		str++;
		len++;
	}
	return (len);
}

void 				history_expansion(char **src_word, size_t *i)
{
	char		c;
	t_history	*history_first;
	int			number_of_history;
	t_history	*history;
	int			history_number;

	c = (*src_word)[*i + 1];
	init_history_num_and_first(&history_first, &number_of_history);
	if (c == '!')
	{
		history = get_history(history_first, number_of_history, -1);
		replace_value(src_word, history->str, i, 2);
	}
	else if (ft_isalpha(c) || c == '-' || ft_isdigit(c))
	{
		history_number = search_history_number(*src_word + 1);
		history = get_history(history_first, number_of_history, history_number);
		replace_value(src_word, history->str, i, 
			find_end_history_expansions(*src_word) - 1);
	}
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
		if (word_state == 0 && (*source_word)[i] == '=')
			inside_assignment_word = 1;
		c = (*source_word)[i];
		if (c == '~')
			try_tilde_expansion(source_word, &i, word_state, inside_assignment_word);
		else if (c == '\\')
			i += 2;
		else if (c == '"')
		{
			word_state ^= IN_DQUOTE_STATE;
			i++;
		}
		else if (c == '\'')
		{
			if (!(word_state & IN_DQUOTE_STATE))
				i += find_closing_quote(*source_word + i) + 1;
			else
				i++;
		}
		else if (c == '$')
			dollar_expansion(source_word, &i, word_state);
		else if (c == '!')
			history_expansion(source_word, &i);
		else
			i++;
	}
	return (expasnion_status(GET_STATUS));
}
