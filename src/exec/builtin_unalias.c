/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:42:37 by nriker            #+#    #+#             */
/*   Updated: 2021/02/23 19:43:23 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		delete_all_aliases(void)
{
	t_hashalias		*hash_alias;
	t_hashtable		*table;
	t_hashtable		*table_c;
	int				i;

	if ((hash_alias = static_hashalias_action(get)) == NULL
		|| hash_alias->hd == NULL)
		return ;
	i = 0;
	while (i < HASH_SIZE)
	{
		table = hash_alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				table_c = table->next;
				delete_alias(table->key);
				table = table_c;
			}
		}
		i++;
	}
}

int			builtin_unalias(char **args, t_env env, int subshell)
{
	t_hashalias		*alias;

	if ((alias = static_hashalias_action(get)) == NULL)
		return (EXIT_FAILURE);
	(void)env;
	(void)subshell;
	if (*args == NULL)
	{
		ft_putstr("unalias: not enough arguments\n");
		return (EXIT_SUCCESS);
	}
	if (!ft_strcmp(*args, "-a"))
	{
		while (*args && !ft_strcmp(*args, "-a"))
			args++;
		delete_all_aliases();
	}
	while (*args)
	{
		if ((delete_alias(*args)) == EXIT_FAILURE)
			ft_printf("unalias: no such hash table element: %s\n", *args);
		args++;
	}
	return (EXIT_SUCCESS);
}
