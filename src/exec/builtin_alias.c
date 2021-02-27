/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/02/27 22:19:46 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

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

int			check_valid_alias_name(char *name)
{
	int		i;

	i = 0;
	while (name[i])
	{
		if (!ft_isalpha(name[i]) && !ft_isalnum(name[i]) && name[i] != '_'
			&& name[i] != '!' && name[i] != '%' && name[i] != ','
			&& name[i] != '@' && name[i] != '-')
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int			builtin_alias_cycle_args(char **mas_args)
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
			if (check_valid_alias_name(mas_args[i]) == EXIT_FAILURE)
			{
				invalid_alias_name(mas_args[i]);
				return (EXIT_FAILURE);
			}
			insert_alias(mas_args[i], mas_args[i + 2]);
			i += 3;
		}
	}
	return (EXIT_SUCCESS);
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
		if ((check_flag_p(&args, print_all_aliases, invalid_alias_option) == EXIT_FAILURE)
			|| ((mas_args = get_alias_args(args, invalid_alias_name)) == NULL)
			|| (builtin_alias_cycle_args(mas_args) == EXIT_FAILURE))
			return (EXIT_FAILURE);
		del_array(mas_args);
	}
	return (EXIT_SUCCESS);
}
