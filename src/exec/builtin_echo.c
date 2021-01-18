/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:18 by anton             #+#    #+#             */
/*   Updated: 2021/01/18 08:26:36 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "environment.h"

/*
** Print all arguments separated by ' '. Print \n.
** Implmented only -n flag which suppresses \n
*/

void			cycle_echo_print(char **args, int n_flag, int e_flag,
					int E_flag)
{
	while (*args)
	{
		ft_putstr(*args);
		if (!n_flag)
			ft_putchar(!*(args + 1) ? '\n' : ' ');
		else if (*(args + 1))
			ft_putchar(' ');
		args++;
	}
}

void			check_echo_flags(char **args)
{
	int		i;
	int		n_flag;
	int		e_flag;
	int		E_flag;

	i = 0;
	// Добавить обработку // - просто удалять из строки лишние /, потом передавать в print
	while (args[i])
	{
		if (!ft_strcmp(args[i], "-n"))
			n_flag = 1;
		else if (!ft_strcmp(args[i], "-e"))
			e_flag = 1;
		else if (!ft_strcmp(args[i], "-E"))
			E_flag = 1;
		else
			break ;
		i++;
	}
	cycle_echo_print(args + i, n_flag, e_flag, E_flag);
}

int	builtin_echo(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	n_flag = 0;
	if (!*args)
		return (1);
	check_echo_flags(args);
	return (1);
}
