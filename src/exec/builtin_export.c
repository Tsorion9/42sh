/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:52:20 by nriker            #+#    #+#             */
/*   Updated: 2021/01/11 00:01:47 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"
#include "t_export.h"
#include "environment.h"
#include "libft.h"

static int handle_export_arg(char *arg)
{
	char *equal;
	char *value;

	if (!(equal = ft_strchr(arg, '=')))
	{
		if (!(value = ft_getenv(env, arg)))
			return (EXIT_FAILURE);
		ft_setenv(export_env, arg, ft_strdup(value));
	}
	else
	{
		*equal = 0;
		ft_setenv(export_env, arg, ft_strdup(equal + 1));
		ft_setenv(env, arg, ft_strdup(equal + 1));
	}
	return (EXIT_SUCCESS);
}

/*
** export -p
** export name[=word]...
*/
int			builtin_export(char **args, t_env env, int subshell)
{
	int status;
	int i;

	(void)args;
	(void)subshell;
	(void)env;
	if (!args || !args[0] || !ft_strcmp(args[0], "-p"))
	{
		print_env(export_env, &status, "export ");
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
