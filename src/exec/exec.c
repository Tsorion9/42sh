#include "21sh.h"
#include "deque.h"
#include "unistd.h"

#include <sys/types.h>
#include <sys/wait.h>

#include "heredoc.h"
#include "t_builtin.h"
#include "task_context.h"
#include "static_env.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "expand.h"

#include "exec_utils.h"
#include "task.h"

/*
** Status of parent process is ignored if there is a child
** in_pipe is a read end
*/

static int	exec_simple(t_simple_cmd *cmd, int in_pipe, int out_pipe)
{
	int				status;
	pid_t			child;
	t_task_context	task_context;
	int				number_of_heredocs;

	number_of_heredocs = n_heredocs(cmd);
	task_context = init_task_context(cmd, in_pipe, out_pipe);
	if (!task_context.need_child)					/* Single process */
		return (task(cmd, &task_context));		   

	if (!(child = fork()))				/* CHILD */
		task(cmd, &task_context);	
	/* This function calls execve, does not return */

	/* Parent */
	if (task_context.in_pipe != IGNORE_STREAM)
		close(in_pipe);
	if (task_context.out_pipe != IGNORE_STREAM)
		close(out_pipe);

	sync_parent_heredoc_state(number_of_heredocs);

	rm_simple_cmd(cmd);
	/* 
	** LAST command in the pipeline; The only command, whose status we care 
	** about. Parent blocks until all children finish (parrent is 21sh, waits for 
	** the last cmd in pipeline)
	** TODO: return status of the last cmd;
	*/
	if (task_context.out_pipe == IGNORE_STREAM)	
		while (wait(&status) > 0) /* Wait returns -1 <==> no children */
			;
	return (status);
}

/*
** By default we should return the status of the last cmd in pipeline
*/

static int	exec_pipeline(t_deque *p)
{
	t_simple_cmd	*cmd;
	t_simple_cmd	*next;
	int				fd[2];
	int				status;
	int				read_fd;

	fd[1] = IGNORE_STREAM;
	cmd = pop_front(p);
	if ((next = pop_front(p)))
		pipe(fd);				/* TODO: check the return value*/
	status = exec_simple(cmd, IGNORE_STREAM, next ? fd[1] : IGNORE_STREAM);
	while (next)
	{
		read_fd = fd[0];		/* For the next process */
		pipe(fd);				/* TODO: check the return value*/
		status = exec_simple(next, read_fd, p->first ? fd[1] : IGNORE_STREAM);
		next = pop_front(p);
	}
	free(p);
	return (status);
}

int	exec_cmd(t_deque *cmd)
{
	t_pipeline	*pipeline;
	int			last_status;

	last_status = 1;
	while ((pipeline = pop_front(cmd)))
	{
		expand_pipeline(pipeline);
		last_status = exec_pipeline(pipeline->commands);
		free(pipeline);
	}
	free(cmd);
	return (last_status);
}
