/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:33 by anton             #+#    #+#             */
/*   Updated: 2021/02/22 23:44:22 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"

t_builtin_and_name	g_builtins[] = {
	{.name = "echo", .function = builtin_echo},
	{.name = "cd", .function = builtin_cd},
	{.name = "getenv", .function = builtin_getenv},
	{.name = "set", .function = builtin_set},
	{.name = "unset", .function = builtin_unset},
	{.name = "exit", .function = builtin_exit},
	{.name = "alias", .function = builtin_alias},
	{.name = "unalias", .function = builtin_unalias},
	{.name = "jobs", .function = builtin_jobs},
	{.name = "bg", .function = builtin_bg},
	{.name = "fg", .function = builtin_fg},
	{.name = "export", .function = builtin_export},
	{.name = "type", .function = builtin_type},
	{.name = "hash", .function = builtin_hash},
	{.name = "fc", .function = builtin_fc},
	{.name = NULL, .function = NULL}
};

t_builtin	get_builtin(char *name)
{
	int	i;

	if (!name)
		return (NULL);
	i = 0;
	while (g_builtins[i].name)
	{
		if (!ft_strcmp(g_builtins[i].name, name))
			return (g_builtins[i].function);
		i++;
	}
	return (NULL);
}
