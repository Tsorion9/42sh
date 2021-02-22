/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:18 by anton             #+#    #+#             */
/*   Updated: 2021/02/15 06:17:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "environment.h"
#include "readline.h"

/*
** Print all arguments separated by ' '. Print \n.
** Implmented only -n flag which suppresses \n
*/

int				print_echo_output(char *args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (args[i] == '\\')
		{
			if (args[i + 1] == 't')
				ft_putchar('\t');
			else if (args[i + 1] == 'n')
				ft_putchar('\n');
			else if (args[i + 1] == 'c')
				return (EXIT_FAILURE);
			else
			{
				ft_putchar(args[i]);
				ft_putchar(args[i + 1]);
			}
			i += 2;
		}
		else
			ft_putchar(args[i++]);
	}
	return (EXIT_SUCCESS);
}

int				cycle_echo_print(char **args, int n_flag, int E_flag)
{
	int	status;

	status = 0;
	if (!*args)
	{
		if (!n_flag)
			ft_putchar('\n');
		return (EXIT_SUCCESS);
	}
	while (*args)
	{
		if (E_flag)
			ft_putstr(*args);
		else
			if (print_echo_output(*args) == EXIT_FAILURE)
				return (EXIT_SUCCESS);
		if (!n_flag)
			status |= (-1 == ft_putchar(!*(args + 1) ? '\n' : ' '));
		else if (*(args + 1))
			status |= (-1 ==ft_putchar(' '));
		args++;
	}
	if (status)
		ft_fprintf(STDERR_FILENO, "%s", "42sh: echo: bad file descriptor\n");
	return (EXIT_SUCCESS);
}

int				check_echo_flags_and_print(char **args)
{
	int		i;
	int		n_flag;
	int		e_flag;
	int		E_flag;

	i = 0;
	n_flag = 0;
	e_flag = 0;
	E_flag = 0;
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
	return (cycle_echo_print(args + i, n_flag, e_flag));
}

int				builtin_echo(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	return (check_echo_flags_and_print(args));
}
