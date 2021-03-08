/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_related_builtins.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:21 by anton             #+#    #+#             */
/*   Updated: 2021/03/08 08:15:35 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "readline.h"

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

static int handle_set_arg(char *arg)
{
	char	*equal;
	char	*key;

	key = NULL;
	if ((equal = ft_strchr(arg, '=')))
	{
		key = ft_strcut(arg, '=');
		ft_setenv(env, key, ft_strdup(equal + 1));
		free(key);
	}
	return (EXIT_SUCCESS);
}

int			builtin_set(char **args, t_env env_deprecated, int subshell)
{
	int		status;
	int		i;

	status = 0;
	(void)subshell;
	(void)env_deprecated;
	if (!*args)
	{
		print_env(env, &status, "");
		return (EXIT_SUCCESS);
	}
	status = EXIT_SUCCESS;
	i = 0;
	while (args[i])
	{
		if (EXIT_FAILURE == handle_set_arg(args[i]))
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}

int			builtin_unset(char **args, t_env env_deprecated, int subshell)
{
	(void)env_deprecated;
	if (subshell)
		return (1);
	while (*args)
	{
		ft_unsetenv(env, *args);
		ft_unsetenv(g_export_env, *args);
		args++;
	}
	return (1);
}
