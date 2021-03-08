/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hash_flags.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:06:38 by nriker            #+#    #+#             */
/*   Updated: 2021/03/08 10:09:20 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

int			check_valid_flag_hash(char *arg, void (*print)(char *arg))
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

void		check_flag_r(char ***args)
{
	static_hash_action(del);
	static_hash_action(init);
	(*args)++;
	while (**args != NULL && !ft_strcmp(**args, "-r"))
		(*args)++;
}

int			check_flag_d(char ***args, void (*invalid_print)(char *arg))
{
	(*args)++;
	while (**args != NULL && (!ft_strcmp(**args, "-r")
		|| !ft_strcmp(**args, "-d")))
		(*args)++;
	return (check_valid_flag_hash(**args, invalid_print));
}

int			check_hash_flags(char ***args, void (*invalid_print)(char *arg))
{
	if (**args != NULL && !ft_strcmp(**args, "-r"))
	{
		check_flag_r(args);
	}
	if (**args != NULL && !ft_strcmp(**args, "-d"))
	{
		if (check_flag_d(args, invalid_print) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		while (**args != NULL)
		{
			delete_hash(**args);
			(*args)++;
		}
	}
	return (check_valid_flag_hash(**args, invalid_print));
}
