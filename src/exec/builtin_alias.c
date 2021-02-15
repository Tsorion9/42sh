/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/02/15 07:18:39 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		check_previous_keys(char *key, char* value)
{
	t_hashalias		*hash_alias;
	t_hashtable		*table;
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
				if (!ft_strcmp(table->value, key))
					insert_alias(table->key, value);
				table = table->next;
			}
		}
		i++;
	}
}

void		check_alias(char *arg)
{
	char	*alias;

	alias = NULL;
	if ((alias = search_alias(arg)) == NULL)
		ft_fprintf(STDERR_FILENO, "42sh: alias: %s: not found\n", arg);
	else
	{
		free(alias);
		alias = NULL;
		print_alias(arg);
	}
}

void		builtin_alias_cycle_args(char **mas_args)
{
	int		i;

	i = 0;
	while (mas_args[i])
	{
		if (mas_args[i] && (mas_args[i + 1] == NULL
			|| ft_strcmp(mas_args[i + 1], "=")))
			check_alias(mas_args[i++]);
		else if (mas_args[i] && !ft_strcmp(mas_args[i + 1], "="))
		{
			insert_alias(mas_args[i], mas_args[i + 2]);
			check_previous_keys(mas_args[i], mas_args[i + 2]);
			i += 3;
		}
	}
}

int			builtin_alias(char **args, t_env env, int subshell)
{
	char	**mas_args;

	mas_args = NULL;
	(void)env;
	(void)subshell;
	if (*args == NULL)
		print_all_aliases();
	else
	{
		if (check_flag_p(&args, print_all_aliases, invalid_alias_option) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((mas_args = get_alias_args(args, invalid_alias_name)) == NULL)
			return (EXIT_FAILURE);
		builtin_alias_cycle_args(mas_args);
		del_array(mas_args);
	}
	return (EXIT_SUCCESS);
}
