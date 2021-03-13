#include "libft.h"
#include "readline.h"

static int	convert_history_number(int history_number, int number_of_history)
{
	if (history_number > number_of_history)
		history_number = number_of_history;
	if (history_number < 0)
	{
		history_number = number_of_history + history_number;
		if (history_number < 1)
			history_number = 1;
	}
	else
	{
		history_number--;
	}
	return (history_number);
}

static void init_number_of_history(int *number_of_history)
{
	t_history	*history;

	history = rp(NULL)->history;
	while (history && history->prev)
		history = history->prev;
	*number_of_history = 0;
	while (history && history->next)
	{
		history = history->next;
		(*number_of_history)++;
	}
}

static char	*search_str_in_history(const char *str)
{
	t_history	*history;
	int			found;
	int			history_number;

	history_number = 0;
	history = rp(NULL)->history;
	found = 0;
	while (history && !found && history_number < HISTSIZE)
	{
		if (ft_strfirststr(history->str, str))
			found = 1;
		if (!found)
		{
			history = history->next;
			history_number++;
		}
	}
	if (!found || history_number >= HISTSIZE)
		return (NULL);
	else
		return (ft_strdup(history->str));
}

static char	*search_history_str(int n)
{
	t_history	*history;
	int			i;

	i = 0;
	history = rp(NULL)->history;
	while (history && history->next)
		history = history->next;
	while (history && history->prev && i < n)
	{
		history = history->prev;
		i++;
	}
	return (ft_strdup(history->str));
}

char		*search_history_subtitution(char *str)
{
	int			history_number;
	int			number_of_history;

	init_number_of_history(&number_of_history);
	if (!str)
		return (NULL);
	if (!ft_strcmp(str, "!!"))
		history_number = -1;
	else if (ft_isnumber(str + 1))
	{
		history_number = ft_atoi(str + 1);
		if (history_number >= HISTSIZE || history_number <= HISTSIZE * (-1))
			return (NULL);
	}
	else
		return (search_str_in_history(str + 1));
	history_number = convert_history_number(history_number, number_of_history);
	return (search_history_str(history_number));
}
