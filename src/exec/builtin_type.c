/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 07:37:50 by nriker            #+#    #+#             */
/*   Updated: 2021/02/09 23:16:27 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_type.h"

int		check_type_input(char *args, t_env env)
{
	if (check_in_alias(args) == EXIT_SUCCESS ||
		check_in_builtins(args) == EXIT_SUCCESS ||
		check_in_path(args, env) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int		builtin_type(char **args, t_env envw, int subshell)
{
	int		i;

	(void)subshell;
	(void)envw;
	if (!*args)
		return (EXIT_SUCCESS);
	i = 0;
	if (args[i][0] == '-')
	{
		invalid_type_option(args[i]);
		return (EXIT_FAILURE);
	}
	while (args[i])
	{
		if (check_type_input(args[i], env) == EXIT_FAILURE)
			invalid_type_name(args[i]);
		i++;
	}
	return (EXIT_SUCCESS);
}
