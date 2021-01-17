/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:42:26 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 17:07:20 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "readline.h"
#include "inc21sh.h"
#include "environment.h"
#include "exec.h"
#include "t_hashalias.h"
#include "t_export.h"

t_env env;

int main(int argc, char **argv, char **envr)
{
    t_complete_cmd *complete_cmd = NULL;

	(void)argc;
	(void)argv;

	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	set_sigint(processing_sigint);
	signal(SIGWINCH, processing_sigwinch);
	signal(SIGTSTP, SIG_IGN);

	int fd;

	if (argc > 1)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			ft_fprintf(2, "21sh: Error! Could not open file: %s\n", argv[1]);
			exit(123);
		}
		dup2(fd, 0);
		close(fd);
	}

	env = init_env(envr);
	static_export_action(init);
	static_hashalias_action(init);
	init_terminal();
	init_prompt();
    rp(init_rp());
	load_on_file_history(rp(NULL)->history);
	while (1)
	{
		complete_cmd = parser();
		set_canon_input_mode(1);
		exec_complete_cmd(complete_cmd);
		set_canon_input_mode(0);
	}
    reset_exit(0);
}
