/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 22:11:49 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 22:11:50 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "inc21sh.h"
#include "environment.h"
#include "exec.h"
#include "t_hashalias.h"
#include "t_export.h"
#include "t_hash.h"

void	set_toplevel_shell_signal(void)
{
	if (!g_interactive_shell)
		return ;
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	set_sigint(processing_sigint);
	signal(SIGWINCH, processing_sigwinch);
	signal(SIGTSTP, SIG_IGN);
}

void	init_readline(void)
{
	if (!g_interactive_shell)
		return ;
	init_terminal();
	init_prompt();
	rp(init_rp());
	load_on_file_history(rp(NULL)->history);
}

void	init_shell(char **envr)
{
	set_toplevel_shell_signal();
	g_env = init_env(envr);
	g_export_env = copy_env(g_env);
	static_hashalias_action(init);
	static_hash_action(init);
	init_readline();
}
