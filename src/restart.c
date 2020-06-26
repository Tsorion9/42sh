/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restart.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 22:06:58 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 22:28:09 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "save_argv.h"
#include "static_env.h"
#include "environment.h"
#include "inc21sh.h"

int	restart_shell(void)
{
	char	**argv;
	t_env	env;
	char	**new_env;
	int		memory_ok;

	argv = global_argv_request(NULL);
	env = static_env_action(get, NULL);
	new_env = to_array(env, &memory_ok);
	reset_input_mode();
	execve(argv[0], argv, new_env);
	write(2, "Could not handle signal. Sorry.\n",\
			sizeof("Could not handle signal. Sorry.\n"));
	return (-1);
}
