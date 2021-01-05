/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/05 13:37:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			builtin_alias(char **args, t_env env, int subshell)
{
	t_hashalias		*alias;

	if ((alias = static_hashalias_action(get)) == NULL)
		return (EXIT_FAILURE);
	(void)env;
	(void)subshell;
	if (*args == NULL)
		alias_api_print_all_aliases(alias);
	else
		while (*args)
		{
			if (*args && args[1] == NULL)
				alias_api_print_alias(*args);
			else if (*args && !ft_strcmp(args[1], "="))
				alias_api_insert_alias(alias, *args, args[2]);
			args++;
		}
	return (EXIT_FAILURE);
}
