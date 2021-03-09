/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:57:30 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 20:57:32 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	child_actions(t_command *cmd, int read_fd, int write_fd)
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
		dup2(read_fd, 0);
		close_wrapper(read_fd);
	}
	if (write_fd != IGNORE_STREAM)
	{
		dup2(write_fd, 1);
		close_wrapper(write_fd);
	}
	code = exec_cmd(cmd);
	exit(code);
}

void	parent_actions(int read_fd, int write_fd)
{
	if (read_fd != IGNORE_STREAM)
	{
		close_wrapper(read_fd);
	}
	if (write_fd != IGNORE_STREAM)
	{
		close_wrapper(write_fd);
	}
}

pid_t	make_child(t_command *cmd, int read_fd, int write_fd,
		int another_read_fd, int need_close)
{
	pid_t	child;

	child = fork();
	if (!child)
	{
		if (need_close)
			close_wrapper(another_read_fd);
		child_actions(cmd, read_fd, write_fd);
	}
	else
	{
		parent_actions(read_fd, write_fd);
	}
	return (child);
}
