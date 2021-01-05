/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:42:37 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 13:33:32 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			builtin_unalias(char **args, t_env env, int subshell)
{
	t_hashalias		*alias;

	if ((alias = static_hashalias_action(get)) == NULL)
		return (EXIT_FAILURE);
	(void)env;
	(void)subshell;
	if (*args == NULL)
		ft_putstr("unalias: not enough arguments\n");
	while (*args)
	{
		if ((unalias_api_delete_alias(&alias, *args)) == EXIT_FAILURE)
			ft_printf("unalias: no such hash table element: %s\n", *args);
		args++;
	}
	return (EXIT_SUCCESS);
}
