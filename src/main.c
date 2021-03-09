/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:42:26 by nriker            #+#    #+#             */
/*   Updated: 2021/02/26 21:47:13 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
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

t_env g_env;
t_env g_export_env;
int g_interactive_shell;
int g_last_cmd_status;
int g_paths_pipefd[2];

static void	set_toplevel_shell_signal(void)
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

static void	init_readline(void)
{
	if (!g_interactive_shell)
		return ;
	init_terminal();
	init_prompt();
	rp(init_rp());
	load_on_file_history(rp(NULL)->history);
}

static void	init_shell(char **envr)
{
	set_toplevel_shell_signal();
	g_env = init_env(envr);
	g_export_env = copy_env(g_env);
	static_hashalias_action(init);
	static_hash_action(init);
	init_readline();
}

static void	read_from_file(char *filename)
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

static void	insert_paths_to_hash(void)
{
	char			*path;
	char			*key;

	path = NULL;
	key = NULL;
	get_next_line(g_paths_pipefd[0], &path);
	while (path)
	{
		key = ft_strcut(path, ':');
		if (key)
		{
			insert_command_to_hash(key, ft_strchr(path, ':') + 1);
			free(key);
		}
		key = NULL;
		free(path);
		path = NULL;
		get_next_line(g_paths_pipefd[0], &path);
	}
}

int			main(int argc, char **argv, char **envr)
{
	t_complete_cmd	*complete_cmd;
	int				flags;

	complete_cmd = NULL;
	if (argc > 1)
		read_from_file(argv[1]);
	g_interactive_shell = isatty(STDIN_FILENO);
	init_shell(envr);
	pipe(g_paths_pipefd);
	flags = fcntl(g_paths_pipefd[0], F_GETFL, 0);
	fcntl(g_paths_pipefd[0], F_SETFL, flags | O_NONBLOCK);
	while (1)
	{
		complete_cmd = parser(NULL);
		set_canon_input_mode(1);
		exec_complete_cmd(complete_cmd);
		insert_paths_to_hash();
		set_canon_input_mode(0);
	}
	reset_exit(0);
}
