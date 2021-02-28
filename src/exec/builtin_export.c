/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:52:20 by nriker            #+#    #+#             */
/*   Updated: 2021/02/15 00:09:03 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"
#include "t_export.h"
#include "environment.h"
#include "libft.h"

static int	handle_export_arg(char *arg)
{
	char	*equal;
	char	*value;
	char	*key;

	key = NULL;
	if ((equal = ft_strchr(arg, '=')))
	{
		key = ft_strcut(arg, '=');
		if (ft_isdigit(*key))
		{
			free(key);
			ft_fprintf(STDERR_FILENO, "42sh: export: bad arg'%s': \n", arg);
			return (EXIT_FAILURE);
		}
		ft_setenv(g_export_env, key, ft_strdup(equal + 1));
		ft_setenv(env, key, ft_strdup(equal + 1));
		free(key);
	}
	else
	{
		value = ft_getenv(env, arg);
		if (value)
			ft_setenv(g_export_env, arg, ft_strdup(value));
	}
	return (EXIT_SUCCESS);
}

/*
** export -p
** export name[=word]...
*/
int			builtin_export(char **args, t_env env_deprecated, int subshell)
{
	int status;
	int i;

	(void)subshell;
	(void)env_deprecated;
	status = 0;
	if (!args || !args[0] || !ft_strcmp(args[0], "-p"))
	{
		print_env(g_export_env, &status, "export ");
		return (EXIT_SUCCESS);
	}
	status = EXIT_SUCCESS;
	i = 0;
	while (args[i])
	{
		if (EXIT_FAILURE == handle_export_arg(args[i]))
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
