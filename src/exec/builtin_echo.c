/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:18 by anton             #+#    #+#             */
/*   Updated: 2021/02/14 00:37:54 by nriker           ###   ########.fr       */
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
	int	minus_n_flag;
	char c = '\n';

	(void)env;
	(void)subshell;
	minus_n_flag = 0;
	if (!*args)
	{
		write(1, &c, 1);
		return (0);
	}
	if (!ft_strcmp(args[0], "-n"))
	{
		minus_n_flag = 1;
		args++;
	}
	while (*args)
	{
		ft_putstr(*args);
		if (!minus_n_flag)
			ft_putchar(!*(args + 1) ? '\n' : ' '); // TODO: Check write errors
		else if (*(args + 1))
			ft_putchar(' ');
		args++;
	}
}

// void			delete_slash_in_echo(char *)



void			check_echo_flags_and_print(char **args)
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
	if (!*args)
		return (1);
	check_echo_flags_and_print(args);
	return (1);
}
