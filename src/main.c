/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:42:26 by nriker            #+#    #+#             */
/*   Updated: 2021/01/08 02:13:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "readline.h"
#include "inc21sh.h"
#include "environment.h"
#include "exec.h"
# include "t_hashalias.h"

t_env env;

int main(int argc, char **argv, char **envr)
{
    t_complete_cmd *complete_cmd = NULL;

	(void)argc;
	(void)argv;

	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGINT, processing_sigint);
	signal(SIGWINCH, processing_sigwinch);
	signal(SIGINT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	env = init_env(envr);
	static_hashalias_action(init);
	init_terminal();
	init_prompt();
    rp(init_rp());
	load_on_file_history(rp(NULL)->history);
	while (1)
	{
		complete_cmd = parser();
		tc_clear_till_end();
		exec_complete_cmd(complete_cmd);
	}
    reset_exit(0);
}
