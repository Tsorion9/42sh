#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "inc21sh.h"
#include "libft.h"
#include "exec.h"
#include "t_builtin.h"
#include "find_exec.h"
#include "job.h"
#include "assignment_word.h"
#include "expand_pipeline.h"
#include "pipeline_words_to_assignments.h"

static int exec_pipeline_job(t_pipeline *pipeline)
{
	int fd[2];
	int read_fd;
	pid_t last_child;

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
	return (wait_all_children(last_child));
}

/*
** Wait for foreground job, from top_level_shell
*/
int wait_fg_job(pid_t job)
{
	int status;
	t_job *j;

	waitpid(job, &status, WUNTRACED);

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

int exec_pipeline(t_pipeline *pipeline)
{
	pid_t job;

	expand_pipeline(pipeline);
	pipeline_words_to_assignments(pipeline);
	if (is_single_builtin(pipeline) || only_assignments(pipeline))
		return (exec_single_builtin(pipeline));
	if (!top_level_shell)
		return (exec_pipeline_job(pipeline));
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
		exit(exec_pipeline_job(pipeline));
	}
}
