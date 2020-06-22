/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 01:48:27 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "21sh.h"

int	g_last_command_status;

/*
** TODO: exit status must be static
*/

int	builtin_exit(char **args, t_env env, int subshell)
{
	(void)env;
	if (subshell)
		return (1);
	if (*args)
		reset_exit(ft_atoi(args[0]));
	else
		reset_exit(g_last_command_status);
	return (1);
}
