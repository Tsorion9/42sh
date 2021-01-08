/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/08 14:43:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		builtin_alias_cycle_args(char **mas_args)
{
	int		i;

	i = 0;
	while (mas_args[i])
	{
		if (mas_args[i] && (mas_args[i + 1] == NULL
			|| ft_strcmp(mas_args[i + 1], "=")))
			print_alias(mas_args[i++]);
		else if (mas_args[i] && !ft_strcmp(mas_args[i + 1], "="))
		{
			insert_alias(mas_args[i], mas_args[i + 2]);
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
		if ((mas_args = get_alias_args(args)) != NULL)
			builtin_alias_cycle_args(mas_args);
		if (mas_args != NULL)
			del_array(mas_args);
	}
	return (EXIT_FAILURE);
}
