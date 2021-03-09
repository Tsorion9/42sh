/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:52:20 by nriker            #+#    #+#             */
/*   Updated: 2021/03/02 00:37:43 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"
#include "t_export.h"
#include "environment.h"
#include "libft.h"

void		invalid_export_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: export: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "export: usage: export [-p] [name ... ]\n");
}

int			check_valid_flag_export(char *arg, void (*print)(char *arg))
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (EXIT_SUCCESS);
	if (arg[i] == '-')
	{
		print(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_valid_export_name(char *name)
{
	char		*key;
	int			i;

	i = 0;
	if (ft_strchr(name, '='))
		key = ft_strcut(name, '=');
	else
		key = ft_strdup(name);
	if (!ft_isalpha(key[i]) && key[i] != '_')
	{
		free(key);
		ft_fprintf(2, "42sh: export: '%s': not a valid identifier\n", key);
		return (EXIT_FAILURE);
	}
	while (key[++i])
	{
		if (!ft_isdigit(key[i]) && !ft_isalpha(key[i]) && key[i] != '_')
		{
			free(key);
			ft_fprintf(2, "42sh: export: '%s': not a valid identifier\n", key);
			return (EXIT_FAILURE);
		}
	}
	free(key);
	return (EXIT_SUCCESS);
}

static int	handle_export_arg(char *arg)
{
	char	*equal;
	char	*key;
	char	*value;

	key = NULL;
	if (check_valid_export_name(arg) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if ((equal = ft_strchr(arg, '=')))
	{
		key = ft_strcut(arg, '=');
		ft_setenv(g_export_env, key, ft_strdup(equal + 1));
		ft_setenv(g_env, key, ft_strdup(equal + 1));
		free(key);
	}
	else
	{
		value = ft_getenv(g_env, arg);
		if (value)
			ft_setenv(g_export_env, arg, ft_strdup(value));
		else
			ft_setenv(g_export_env, arg, ft_strdup(""));
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
	if (!args || !args[0] || !ft_strcmp(args[0], "-p"))
	{
		print_env(g_export_env, &status, "export ");
		return (EXIT_SUCCESS);
	}
	if (check_valid_flag_export(*args, invalid_export_option) == EXIT_FAILURE)
		return (EXIT_FAILURE);
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
