/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:36:41 by nriker            #+#    #+#             */
/*   Updated: 2021/01/09 01:42:33 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			check_valid_symbol(char c, char *key, char *copy, int i)
{
	if (c == '\'' || c == '"' ||
		(c == '\\' && c == '\0'))
		delete_symbol_in_str(key, i);
	else if (c == '\\' && c != '\0')
	{
		ft_printf("alias: '%s': invalid alias name\n", copy);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_valid_flag(char *arg)
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (EXIT_SUCCESS);
	while (arg[i] == '\\')
		i++;
	if (arg[i] == '-')
	{
		ft_printf("42sh: alias: %s: invalid option\n", arg);
		ft_putstr("alias: usage: alias [-p] [name[=value] ... ]\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_flags(char ***args)
{
	if (**args != NULL && !ft_strcmp(**args, "-p"))
	{
		print_all_aliases();
		(*args)++;
		while (**args != NULL && !ft_strcmp(**args, "-p"))
			(*args)++;
		return (check_valid_flag(**args));
	}
	return (check_valid_flag(**args));
}
