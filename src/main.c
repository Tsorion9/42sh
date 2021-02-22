/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:42:26 by nriker            #+#    #+#             */
/*   Updated: 2021/02/22 17:18:10 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE             /* See feature_test_macros(7) */
#include <fcntl.h>              /* Obtain O_* constant definitions */
#include <unistd.h>

#include <unistd.h>
#include <signal.h>
#include "lexer.h"
#include "parser.h"
#include "readline.h"
#include "inc21sh.h"
#include "environment.h"
#include "exec.h"
#include "t_hashalias.h"
#include "t_export.h"
#include "t_hash.h"

t_env env;
t_env export_env;
int interactive_shell;
int last_cmd_status;
int paths_pipefd[2];

static void set_toplevel_shell_signal(void)
{
	if (!interactive_shell)
		return ;
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	set_sigint(processing_sigint);
	signal(SIGWINCH, processing_sigwinch);
	signal(SIGTSTP, SIG_IGN);
}

static void init_readline(void)
{
	if (!interactive_shell)
		return ;
	init_terminal();
	init_prompt();
    rp(init_rp());
	load_on_file_history(rp(NULL)->history);
}

static void init_shell(char **envr)
{
	set_toplevel_shell_signal();
	env = init_env(envr);
	export_env = copy_env(env);
	static_hashalias_action(init);
	static_hash_action(init);
	init_readline();
}

static void read_from_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		ft_fprintf(2, "42sh: Error! Could not open file: %s\n", filename);
		exit(123);
	}
	dup2(fd, STDIN_FILENO);
	close_wrapper(fd);
}

int main(int argc, char **argv, char **envr)
{
    t_complete_cmd	*complete_cmd = NULL;
	char			*path;
	char			*key;
	
	path = NULL;
	key = NULL;
	if (argc > 1)
	{
		read_from_file(argv[1]);
	}
	interactive_shell = isatty(STDIN_FILENO);
	init_shell(envr);
	pipe(paths_pipefd);
	fcntl(paths_pipefd[0], O_NONBLOCK);
	while (1)
	{
		complete_cmd = parser(NULL);
		set_canon_input_mode(1);
		exec_complete_cmd(complete_cmd);
		get_next_line(paths_pipefd[0], &path);
		while (path)
		{
			// get_next_line(paths_pipefd[i], &path);
			key = ft_strcut(path, ':');
			insert_hash(key, ft_strchr(path, ':') + 1);
			if (key)
				free(key);
			key = NULL;
			// ft_printf("%s\n", path);
			free(path);
			path = NULL;
			get_next_line(paths_pipefd[0], &path);
		}
		set_canon_input_mode(0);
	}
    reset_exit(0);
}
