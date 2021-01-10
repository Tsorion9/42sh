/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_p.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 01:36:41 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 22:30:32 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"
#include "t_export.h"

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

int			check_flag_pn(char ***args, void	(*print)(void),
				void (*invalid_print)(char *arg))
{
	t_export		*export;

	if ((export = static_export_action(get)) == NULL)
		return (EXIT_FAILURE);
	if (**args != NULL && (!ft_strcmp(**args, "-n")
		|| !ft_strcmp(**args, "-p")))
	{
		if (!ft_strcmp(**args, "-p"))
			print();
		else if (!ft_strcmp(**args, "-n"))
			export->flag_n = 1;
		(*args)++;
		while (**args != NULL && (!ft_strcmp(**args, "-n")
			|| !ft_strcmp(**args, "-p")))
			(*args)++;
		return (check_valid_flag(**args, invalid_print));
	}
	return (check_valid_flag(**args, invalid_print));
}

int			check_flag_p(char ***args, void	(*print)(void),
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
