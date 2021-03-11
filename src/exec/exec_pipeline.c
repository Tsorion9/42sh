/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:22:17 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 01:02:22 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "inc21sh.h"
#include "libft.h"
#include "exec.h"
#include "job.h"
#include "expand_pipeline.h"
#include "pipeline_words_to_assignments.h"

static int	exec_pipeline_job(t_pipeline *pipeline)
{
	int		fd[2];
	int		rw_fd[2];
	int		read_fd;
	pid_t	last_child;
	int		first_iter;

	first_iter = 1;
	if (!pipeline)
		exit(g_last_cmd_status);
	fd[0] = IGNORE_STREAM;
	while (pipeline && pipeline->command)
	{
		read_fd = fd[0];
		fd[1] = IGNORE_STREAM;
		if (pipeline->next)
		{
			pipe(fd);
		}
		rw_fd[0] = read_fd;
		rw_fd[1] = fd[1];
		last_child = make_child(pipeline->command, rw_fd, fd[0], first_iter);
		first_iter = 0;
		pipeline = pipeline->next;
	}
	return (wait_all_children(last_child));
}

/*
** Wait for foreground job, from top_level_shell
*/

int			wait_fg_job(pid_t job)
{
	int		status;
	t_job	*j;

	waitpid(job, &status, WUNTRACED);
	j = find_job(job);
	j->state = job_status_to_state(status);
	j->status = status;
	if (WIFSTOPPED(status))
		kill(j->pgid, SIGCONT);
	if (j->state != DONE)
		j->priority = next_priority();
	if (j->state == DONE)
		remove_job(job);
	if ((j = find_job(job)) && g_interactive_shell)
		tcgetattr(STDIN_FILENO, &(j->tmodes));
	if (g_interactive_shell)
	{
		tcsetpgrp(STDIN_FILENO, getpid());
		set_shell_input_mode();
	}
	return (status);
}

static int	pipeline_word_exp(t_pipeline *pipeline)
{
	if (expand_pipeline(pipeline) == EXPANSION_FAIL)
		return (1);
	pipeline_words_to_assignments(pipeline);
	pipeline_field_splitting(pipeline);
	pipeline_pathname_expansion(pipeline);
	pipeline_quote_removal(pipeline);
	return (0);
}

static int	pipeline_parent_actions(t_pipeline *pipeline, pid_t job)
{
	add_job(job, 0, get_pipeline_str(pipeline));
	if (g_interactive_shell)
	{
		setpgid(job, job);
		tcsetpgrp(STDIN_FILENO, job);
	}
	return (wait_fg_job(job));
}

int			exec_pipeline(t_pipeline *pipeline)
{
	pid_t job;

	if (pipeline_word_exp(pipeline))
		return (1);
	if (is_single_builtin(pipeline) || only_assignments(pipeline))
		return (exec_single_builtin(pipeline));
	if (!g_top_level_shell)
		return (exec_pipeline_job(pipeline));
	job = fork();
	if (job)
		return (pipeline_parent_actions(pipeline, job));
	else
	{
		if (g_interactive_shell)
		{
			setpgid(getpid(), getpid());
			tcsetpgrp(STDIN_FILENO, getpid());
			set_jobshell_signal();
		}
		g_top_level_shell = 0;
		exit(exec_pipeline_job(pipeline));
	}
}
