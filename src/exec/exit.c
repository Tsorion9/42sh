/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 16:25:23 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "inc21sh.h"

int	last_cmd_status(int need_update, int new_value)
{
	static int	g_last_command_status;

	if (need_update)
		g_last_command_status = new_value;
	return (g_last_command_status);
}

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
		reset_exit(last_cmd_status(0, 0));
	return (1);
}
