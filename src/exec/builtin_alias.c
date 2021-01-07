/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/07 10:31:20 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			builtin_alias(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	if (*args == NULL)
		print_all_aliases();
	else
		while (*args)
		{
			if (*args && (args[1] == NULL || ft_strcmp(args[1], "=")))
				print_alias(*args);
			else if (*args && !ft_strcmp(args[1], "="))
				insert_alias(*args, args[2]);
			args++;
		}
	return (EXIT_FAILURE);
}
