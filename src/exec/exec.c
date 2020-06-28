/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:22 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 23:43:22 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
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
#include "fd_crutch.h"

int			have_children_global_request(int set_value, int value)
{
	static int	have_children;

	if (set_value == 1)
		have_children = value;
	return (have_children);
}

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

	status = 0;
	number_of_heredocs = n_heredocs(cmd);
	task_context = init_task_context(cmd, in_pipe, out_pipe);
	if (!task_context.need_child)
		return (task(cmd, &task_context));
	if (!(child = fork()))
		task(cmd, &task_context);
	have_children_global_request(1, 1);
	if (task_context.in_pipe != IGNORE_STREAM)
		close(in_pipe);
	if (task_context.out_pipe != IGNORE_STREAM)
		close(out_pipe);
	sync_parent_heredoc_state(number_of_heredocs);
	rm_simple_cmd(cmd);
	if (task_context.out_pipe == IGNORE_STREAM)
		while (wait(&status) > 0)
			;
	have_children_global_request(1, 0);
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
		pipe_wrapper(fd);
	status = exec_simple(cmd, IGNORE_STREAM, next ? fd[1] : IGNORE_STREAM);
	while (next)
	{
		read_fd = fd[0];
		if (deque_len(p))
			pipe_wrapper(fd);
		status = exec_simple(next, read_fd,\
				deque_len(p) ? fd[1] : IGNORE_STREAM);
		close(read_fd);
		close(fd[1]);
		next = pop_front(p);
	}
	free(p);
	return (status);
}

int			exec_cmd(t_deque *cmd)
{
	t_pipeline	*pipeline;
	int			last_status;

	last_status = 1;
	set_canon_input_mode(1);
	while ((pipeline = pop_front(cmd)))
	{
		expand_pipeline(pipeline);
		last_status = exec_pipeline(pipeline->commands);
		free(pipeline);
	}
	free(cmd);
	set_canon_input_mode(0);
	return (last_status);
}
