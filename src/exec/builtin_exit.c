/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:25 by anton             #+#    #+#             */
/*   Updated: 2021/01/09 21:45:26 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "inc21sh.h"
#include "libft.h"

static int	check_exit_status(char *status)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(status);
	if (len > 19)
		return (FUNC_FAIL);
	else
	{
		i = 0;
		while (status[i] != '\0')
		{
			if (ft_isdigit(status[i]) == 0)
				return (FUNC_FAIL);
			i++;
		}
	}
	return (FUNC_SUCCESS);
}

/*
** TODO: exit status must be static
** return 1 if error occurred, else 0 - success
*/

int			builtin_exit(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	if (args[0] != NULL && args[1] == NULL)
	{
		if (check_exit_status(args[0]) == FUNC_SUCCESS)
			reset_exit(args[0] ? ft_atoi(args[0]) : 0);
		ft_fprintf(STDERR_FILENO, "42sh: exit: %s: %s",
				args[0], E_NUMERIC_ARG_REQUIRED);
		reset_exit(255);
	}
	else if (args[0] != NULL && args[1] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "%s\n", E_TOO_MANY_ARGS);
		return (1);
	}
	else
		reset_exit(args[0] ? ft_atoi(args[0]) : 0);
	return (0);
}
