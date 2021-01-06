#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "readline.h"
#include "inc21sh.h"
#include "environment.h"
#include "exec.h"

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
	if (async_notify_bg)
	{
		signal(SIGCHLD, &sigchld_handler);
	}

	env = init_env(envr);
	init_terminal();
	init_prompt();
    rp(init_rp());
	load_on_file_history(rp(NULL)->history);
	while (1)
	{
		complete_cmd = parser();
		exec_complete_cmd(complete_cmd);
	}
    reset_exit(0);
}
