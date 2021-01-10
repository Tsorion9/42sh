/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:52:20 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:24:20 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"
#include "t_export.h"

void		check_export(char *arg)
{
	char	*alias;

	alias = NULL;
	if ((alias = search_alias(arg)) == NULL)
		ft_printf("42sh: export: %s: not found\n", arg);
	else
	{
		free(alias);
		alias = NULL;
		print_alias(arg);
	}
}

void		builtin_export_cycle_args(char **mas_args)
{
	int		i;

	i = 0;
	while (mas_args[i])
	{
		if (mas_args[i] && (mas_args[i + 1] == NULL
			|| ft_strcmp(mas_args[i + 1], "=")))
			check_export(mas_args[i++]);
		else if (mas_args[i] && !ft_strcmp(mas_args[i + 1], "="))
		{
			insert_export(mas_args[i], mas_args[i + 2]);
			i += 3;
		}
	}
}

int			builtin_export(char **args, t_env env, int subshell)
{
	char	**mas_args;

	mas_args = NULL;
	(void)args;
	(void)subshell;
	(void)env;
	if (*args == NULL)
		print_exports();
	else
	{
		if (check_flags(&args, print_exports, invalid_export_option) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		if ((mas_args = get_alias_args(args, invalid_export_name), invalid_export_name) == NULL)
			return (EXIT_FAILURE);
		builtin_export_cycle_args(mas_args);
		del_array(mas_args);
	}
	return (EXIT_SUCCESS);
}
