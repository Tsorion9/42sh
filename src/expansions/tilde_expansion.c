/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 18:14:44 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 18:15:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "lexer.h"
#include "environment.h"

/*
** @param str строка в которой происходит подстановка
** @param value значение подстановки
** @param start стартовый индекс начала подстановки
** @param len длина подстроки вместо которой будет подставляться value
** Example: replace_value(&"foo", "bar", &0, 3)
** Result:  "bar"
*/

int		replace_value(char **str, char *value, size_t *start, size_t len)
{
	char	*fresh;
	size_t	value_len;

	if (value != NULL)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	if ((fresh = ft_strnew(ft_strlen(*str) - len + value_len)) == NULL)
		return (FUNC_ERROR);
	ft_strncpy(fresh, *str, *start);
	if (value != NULL)
		ft_strcat(fresh, value);
	ft_strcat(fresh, &(*str)[*start + len]);
	ft_strdel(str);
	*str = fresh;
	*start += value_len;
	return (FUNC_SUCCESS);
}

char	*get_login(char *s, size_t i)
{
	size_t	login_len;

	i++;
	login_len = 0;
	while (s[i] != '\0' && s[i] != '/')
	{
		i++;
		login_len++;
	}
	if (login_len == 0)
		return (ft_strnew(0));
	return (ft_strsub(s, i - login_len, login_len));
}

/*
** If HOME is unset, results are unspecified by POSIX
*/

int		get_user_home_path(char *login, char **home_path,
						int inside_assignment_word)
{
	struct passwd	*user_info;

	if (login[0] == '\0' || (login[0] == ':' && inside_assignment_word == 1))
	{
		*home_path = ft_getenv(env, "HOME");
		if (*home_path == NULL)
			return (FUNC_ERROR);
	}
	else
	{
		user_info = getpwnam(login);
		if (user_info == NULL)
			return (FUNC_ERROR);
		*home_path = user_info->pw_dir;
	}
	return (FUNC_SUCCESS);
}

/*
** @param s строка в которой выполняется расширение тильды
** @param i индекс в строке
*/

int		tilde_expansion(char **s, size_t *i, int inside_assignment_word)
{
	char	*login;
	char	*home_path;
	int		ret;

	home_path = NULL;
	if ((login = get_login(*s, *i)) == NULL)
		return (FUNC_ERROR);
	if (get_user_home_path(login, &home_path, inside_assignment_word) == -1)
	{
		ft_strdel(&login);
		(*i)++;
		return (FUNC_ERROR);
	}
	ret = replace_value(s, home_path, i,
						login[0] == ':' ? 1 : ft_strlen(login) + 1);
	ft_strdel(&login);
	return (ret);
}
