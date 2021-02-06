/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_related_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:21 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

int			builtin_getenv(char **args, t_env env_deprecated, int subshell)
{
	char	*c;

	(void)env_deprecated;
	if (subshell)
		return (1);
	if (!args[0])
	{
		ft_printf("%s", "Usage: getenv name\n");
		return (0);
	}
	while (*args)
	{
		c = ft_getenv(env, args[0]);
		if (!c)
			ft_printf("No such variable in env: %s\n", args[0]);
		else
			ft_printf("%s=%s\n", args[0], c);
		args++;
	}
	return (1);
}

/*
** According to POSIX, names shall not contain '='
** https://pubs.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html
** Bash also does not tolerate ':', but we do
*/

int			builtin_set(char **args, t_env env_deprecated, int subshell)
{
	char	*tmp;

	(void)env_deprecated;
	if (subshell)
		return (1);
	if (!*args)
		return (1);
	if (*args && !*(args + 1))
	{
		ft_setenv(env, *args, ft_strdup(""));
		return (1);
	}
	tmp = *args;
	while (*tmp)
	{
		if (*tmp == '=')
			return (1);
		tmp++;
	}
	if (!ft_setenv(env, *args, ft_strdup(*(args + 1))))
	{
		ft_printf("Error: Could not set env\n");
		return (0);
	}
	return (1);
}

int			builtin_unset(char **args, t_env env_deprecated, int subshell)
{
	(void)env_deprecated;
	if (subshell)
		return (1);
	while (*args)
	{
		ft_unsetenv(env, *args);
		ft_unsetenv(export_env, *args);
		args++;
	}
	return (1);
}
