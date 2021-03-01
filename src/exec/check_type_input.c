/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type_input.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:12:12 by nriker            #+#    #+#             */
/*   Updated: 2021/03/02 01:00:26 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_type.h"

int		check_in_path(char *args, t_env env)
{
	char	*path;

	path = NULL;
	if ((path = find_path(args)) != NULL)
	{
		ft_printf("%s is %s\n", args, path);
		free(path);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		check_in_builtins(char *args)
{
	if (!ft_strcmp(args, "echo") || !ft_strcmp(args, "cd") ||
		!ft_strcmp(args, "set") ||
		!ft_strcmp(args, "unset") || !ft_strcmp(args, "exit") ||
		!ft_strcmp(args, "21shopt") || !ft_strcmp(args, "alias") ||
		!ft_strcmp(args, "unalias") || !ft_strcmp(args, "jobs") ||
		!ft_strcmp(args, "bg") || !ft_strcmp(args, "fg") ||
		!ft_strcmp(args, "export") ||
		!ft_strcmp(args, "type") || !ft_strcmp(args, "hash"))
	{
		ft_printf("%s is a shell builtin\n", args);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		check_in_hash(char *args)
{
	char	*value;

	if ((value = search_hash(args)))
	{
		ft_printf("%s is hashed (%s)\n", args, value);
		free(value);
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int		check_in_alias(char *args)
{
	char	*alias;

	alias = NULL;
	if ((alias = search_alias(args)) != NULL)
	{
		ft_printf("%s is aliased to '%s'\n", args, alias);
		free(alias);
		alias = NULL;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}
