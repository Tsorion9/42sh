#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

#include "inc21sh.h"
#include "libft.h"
#include "exec.h"
#include "t_builtin.h"
#include "find_exec.h"
#include "job.h"

int tmp_lstlen(t_word_list *w)
{
	int l;

	l = 0;
	while (w)
	{
		w = w->next;
		l++;
	}
	return (l);
}

/*
** Translate list to array
*/
char **collect_argwords(t_word_list *words)
{
	int		l;
	char	**res;
	int		i;

	i = 0;
	l = tmp_lstlen(words);
	res = ft_memalloc(sizeof(char *) * (l + 1));
	while (words && words->word)
	{
		res[i++] = ft_strdup(words->word);
		words = words->next;
	}
	return (res);
}

void make_assignments_redirections(t_simple_cmd *cmd)
{
	(void)cmd;
	//TODO
	return ;
}

int exec_simple_cmd(t_simple_cmd *cmd)
{
	t_word_list *words;
	char **args;
	int save_fd[3];
	t_builtin builtin;
	int status;

	save_fd[0] = dup(STDIN_FILENO);
	save_fd[1] = dup(STDOUT_FILENO);
	save_fd[2] = dup(STDERR_FILENO);

	make_assignments_redirections(cmd);
	words = cmd->words;
	args = collect_argwords(words);
	builtin = get_builtin(words->word);
	if (builtin)
	{
		status = builtin(args + 1, env, 0);
	}
	else
	{
		status = find_exec(args, env);
	}

	dup2(save_fd[0], STDIN_FILENO);
	dup2(save_fd[1], STDOUT_FILENO);
	dup2(save_fd[2], STDERR_FILENO);
	close(save_fd[0]);
	close(save_fd[1]);
	close(save_fd[2]);
	return (status);
}


int exec_cmd(t_command *cmd)
{
	if (!cmd->simple_cmd) {
		ft_printf("%s\n", "Only simple commands implemented yet");
		return (-1);
	}
	return (exec_simple_cmd(cmd->simple_cmd));
}

void child_actions(t_command *cmd, int read_fd, int write_fd)
{
	int code;
	
	signal(SIGTERM, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGUSR1, SIG_DFL);

	if (read_fd != IGNORE_STREAM)
	{
		dup2(read_fd, 0); /* TODO: Handle errors here*/
		close(read_fd);
	}
	if (write_fd != IGNORE_STREAM)
	{
		dup2(write_fd, 1);
		close(write_fd);
	}
	code = exec_cmd(cmd);
	exit(code); /* In case of builtin */
}

void parent_actions(int read_fd, int write_fd)
{
	if (read_fd != IGNORE_STREAM)
	{
		close(read_fd);
	}
	if (write_fd != IGNORE_STREAM)
	{
		close(write_fd);
	}
}

pid_t	make_child(t_command *cmd, int read_fd, int write_fd)
{
	pid_t	child;

	child = fork();
	if (!child) /* Child, exits*/
	{
		child_actions(cmd, read_fd, write_fd);
	}
	else
	{
		parent_actions(read_fd, write_fd);
	}
	return (child);
}

int exec_pipline_job(t_pipeline *pipeline)
{
	int fd[2];
	int read_fd;
	pid_t last_child;
	int status;
	pid_t finished;
	int last_child_status;

	if (!pipeline)
		exit(0);
	fd[0] = IGNORE_STREAM;
	while (pipeline && pipeline->command)
	{
		read_fd = fd[0];
		fd[1] = IGNORE_STREAM;
		if (pipeline->next)
		{
			pipe(fd);
		}
		last_child = make_child(pipeline->command, read_fd, fd[1]);
		pipeline = pipeline->next;
	}

	/* collect exit status of latest child, do not return until every child dies*/
	while ((finished = wait(&status)) != -1)
	{
		if (finished == last_child)
		{
			last_child_status = status;
		}
	}
	if (WCOREDUMP(last_child_status)) /*Special case of WIFSIGNALED*/
	{
		signal(SIGSEGV, SIG_DFL);
		kill(getpid(), SIGSEGV);  //Fucking genious
	}
	if (WIFSIGNALED(last_child_status))
	{
		signal(WTERMSIG(last_child_status), SIG_DFL);
		kill(getpid(), WTERMSIG(last_child_status));  //Fucking genious
	}
	if (WIFSTOPPED(last_child_status))
		return (WSTOPSIG(last_child_status));
	return (WEXITSTATUS(last_child_status));
}

int is_single_builtin(t_pipeline *pipeline)
{
	t_word_list *words;

	if (!pipeline->next)
	{
		if (pipeline->command->cmd_type == SIMPLE_CMD)
		{
			words = pipeline->command->simple_cmd->words;
			if (words && get_builtin(words->word))
			{
				return (1);
			}
		}
		return (0);
	}
	return (0);
}

int exec_single_builtin(t_pipeline *pipeline)
{
	return (exec_cmd(pipeline->command));
}

/*
** Wait for foreground job, from top_level_shell
*/
int wait_fg_job(pid_t job)
{
	int status;
	t_job *j;

	waitpid(job, &status, WUNTRACED | WCONTINUED);

	j = find_job(job);
	j->state = job_status_to_state(status);
	j->status = status;
	if (j->state != DONE)
	{
		j->priority = next_priority();
	}
	if (j->state == DONE)
	{
		remove_job(job);
	}

	if ((j = find_job(job)))
	{
		tcgetattr(STDIN_FILENO, &(j->tmodes));
	}
	/* Put top-level shell to foreground*/
	tcsetpgrp(STDIN_FILENO, getpid());
	set_shell_input_mode();
	return (0);
}

int exec_pipline(t_pipeline *pipeline)
{
	pid_t job;

	if (is_single_builtin(pipeline))
	{
		return (exec_single_builtin(pipeline));
	}
	if (!top_level_shell)
	{
		return (exec_pipline_job(pipeline));
	}
	job = fork();
	if (job) /* Top-level shell */
	{
		add_job(job, 0, get_pipeline_str(pipeline));
		setpgid(job, job);
		tcsetpgrp(STDIN_FILENO, job);
		return (wait_fg_job(job)); /* Job is in foreground */
	}
	else /* Job shell */
	{
		setpgid(getpid(), getpid());
		tcsetpgrp(STDIN_FILENO, getpid()); /* We are foreground */
		set_jobshell_signal();
		top_level_shell = 0;
		exit(exec_pipline_job(pipeline));
	}
}
