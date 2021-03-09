/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_all_children.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:51:54 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 20:51:55 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

/*
** Return exit status of last child
*/

int	wait_all_children(pid_t last_child)
{
	pid_t	finished;
	int		last_child_status;
	int		status;

	while ((finished = waitpid(-1, &status, WUNTRACED | WCONTINUED)) != -1)
	{
		if (finished == last_child)
			last_child_status = status;
	}
	if (WCOREDUMP(last_child_status))
	{
		signal(SIGSEGV, SIG_DFL);
		kill(getpid(), SIGSEGV);
	}
	if (WIFSIGNALED(last_child_status))
	{
		signal(WTERMSIG(last_child_status), SIG_DFL);
		kill(getpid(), WTERMSIG(last_child_status));
	}
	if (WIFSTOPPED(last_child_status))
		return (WSTOPSIG(last_child_status));
	return (WEXITSTATUS(last_child_status));
}
