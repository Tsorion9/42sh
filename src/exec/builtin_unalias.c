/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:42:37 by nriker            #+#    #+#             */
/*   Updated: 2021/03/01 23:08:55 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		invalid_unalias_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: unalias: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "unalias: usage: unalias [-a] [name ... ]\n");
}

int			check_valid_flag_unalias(char *arg, void (*print)(char *arg))
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

int			unalias_cycle_params(char **args)
{
	int				status;

	status = EXIT_SUCCESS;
	while (*args)
	{
		if ((delete_alias(*args)) == EXIT_FAILURE)
		{
			ft_printf("unalias: no such hash table element: %s\n", *args);
			status = EXIT_FAILURE;
		}
		args++;
	}
	return (status);
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
		delete_all_aliases();
		return (EXIT_SUCCESS);
	}
	if (check_valid_flag_unalias(*args, invalid_unalias_option) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (unalias_cycle_params(args));
}
