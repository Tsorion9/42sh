#include "21sh.h"

/*
** Проверяет, является ли '\', с индексом start_check, цитированием.
*/

int		check_backslash(char *user_in, int start_check)
{
	int res;

	if (start_check < 0)
		return (1);
	res = 1;
	while (user_in[start_check] == '\\' && start_check >= 0)
	{
		res++;
		start_check--;
	}
	return (res % 2);
}

/*
** Проверяет необходимость перевода на новую строку.
*/

void	check_flag(char *user_in, char *flag)
{
	int i;

	i = 0;
	while (user_in[i])
	{
		if (user_in[i] == *flag && *flag == '\'')
			*flag = 0;
		else if (user_in[i] == '\"' && user_in[i] == *flag\
			&& check_backslash(user_in, i - 1) == 1)
			*flag = 0;
		else if ((user_in[i] == '\'' || user_in[i] == '\"') && *flag == 0\
			&& check_backslash(user_in, i - 1) == 1)
			*flag = user_in[i];
		i++;
	}
}
