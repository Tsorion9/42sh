/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:36:41 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:25:11 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			check_valid_symbol(char *key, char *copy, int i,
				void (*print)(char	*copy))
{
	if (key[i] == '\'' || key[i] == '"' ||
		(key[i] == '\\' && key[i + 1] == '\0'))
		delete_symbol_in_str(key, i);
	else if (key[i] == '\\' && key[i + 1] != '\0')
	{
		print(copy);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_valid_flag(char *arg, void (*print)(char *arg))
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (EXIT_SUCCESS);
	while (arg[i] == '\\')
		i++;
	if (arg[i] == '-')
	{
		print(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_flags(char ***args, void	(*print)(void),
				void (*invalid_print)(char *arg))
{
	if (**args != NULL && !ft_strcmp(**args, "-p"))
	{
		print();
		(*args)++;
		while (**args != NULL && !ft_strcmp(**args, "-p"))
			(*args)++;
		return (check_valid_flag(**args, invalid_print));
	}
	return (check_valid_flag(**args, invalid_print));
}
