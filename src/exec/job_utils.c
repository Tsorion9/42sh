/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 00:58:51 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 00:59:36 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

/*
** Create new job if not exists
** Add PID to list of pids if job exists
*/

void		add_job(int pgid, int background, char *cmd_line)
{
	t_job		*new;
	static int	id;

	new = ft_memalloc(sizeof(t_job));
	new->pgid = pgid;
	new->state = background ? BACKGROUND : FG;
	new->jobid = id++;
	new->priority = 0;
	new->cmdline = cmd_line;
	tcgetattr(STDIN_FILENO, &(new->tmodes));
	if (new->state == BACKGROUND)
	{
		new->priority = next_priority();
	}
	ft_lstadd_data(&g_jobs, new, 0);
}

char		*job_state_tostr(t_job_state s)
{
	if (s == FG || s == BACKGROUND)
		return (ft_strdup("Running"));
	if (s == STOPPED)
		return (ft_strdup("Stopped"));
	return (ft_strdup("Done"));
}

/*
** Find by pgid
*/

t_job		*find_job(pid_t pgid)
{
	t_list	*l;

	l = g_jobs;
	while (l)
	{
		if (((t_job *)l->content)->pgid == pgid)
			return (((t_job *)l->content));
		l = l->next;
	}
	return (NULL);
}

t_job_state	job_status_to_state(int status)
{
	if (WIFSTOPPED(status))
		return (STOPPED);
	if (WIFCONTINUED(status))
		return (BACKGROUND);
	if (WIFEXITED(status))
		return (DONE);
	if (WCOREDUMP(status))
		return (DONE);
	if (WIFSIGNALED(status))
		return (DONE);
	return (FG);
}

void		update_job_state(pid_t job, t_job_state new_state, int status)
{
	t_job	*j;

	j = find_job(job);
	if (j)
	{
		j->state = new_state;
		j->status = status;
	}
}
