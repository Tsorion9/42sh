#include "libft.h"
#include "job.h"

t_list *jobs;

int next_priority(void)
{
	static int priority;	

	priority++;
	return (priority);
}

void update_job_priority(pid_t j)
{
	t_job *job;

	job = find_job(j);
	if (job)
	{
		job->priority = next_priority();
	}
}

/*
** Set numbers of maximum and second maximum priority
*/
void biggest_priorities(int *max, int *second_max)
{
	t_job *j;
	t_list *l;

	*max = -1;
	*second_max = -1;
	l = jobs;
	while (l)
	{
		j = (t_job *)(l->content);
		if (j->priority > *max)
		{
			if (ft_lstlen(jobs) > 1)
			{
				*second_max = *max;
			}
			*max = j->priority;
		}
		else if (j->priority > *second_max && ft_lstlen(jobs) > 1)
		{
			*second_max = j->priority;
		}
		l = l->next;
	}
}

/*
** Create new job if not exists
** Add PID to list of pids if job exists
*/
void add_job(int pgid, int background)
{
	t_job *new;
	static int id;

	new = ft_memalloc(sizeof(t_job));
	new->pgid = pgid;
	new->state = background ? BACKGROUND : FG;
	new->jobid = id++;
	new->priority = 0;
	if (new->state == BACKGROUND)
	{
		new->priority = next_priority();
	}
	ft_lstadd_data(&jobs, new, 0);
}

void destroy_job(void *j, size_t content_size)
{
	(void)content_size;
	free(((t_job *)j)->cmdline);
	free((t_job *)j);
}

void remove_job(int pgid)
{
	t_job *delete_me;
	t_list *prev;
	t_list *tmp;

	delete_me = find_job(pgid);

	if (delete_me == jobs->content) /* Del first */
	{
		prev = jobs;
		jobs = jobs->next;
		ft_lstdelone(&prev, destroy_job);
	}

	prev = jobs;
	while (prev)
	{
		if (prev->next && (prev->next->content == delete_me))
		{
			break ;
		}
		prev = prev->next;
	}

	if (delete_me && prev)
	{
		tmp = prev->next;
		prev->next = prev->next->next;
		ft_lstdelone(&tmp, destroy_job);
		return ;
	}
}

/*
** Find by pgid
*/
t_job *find_job(pid_t pgid)
{
	t_list	*l;

	l = jobs;
	while (l)
	{
		if (((t_job *)l->content)->pgid == pgid)
		{
			return (((t_job *)l->content));
		}
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
	return (DONE);
}

void update_job_state(pid_t job, t_job_state new_state)
{
	t_job *j;

	j = find_job(job);
	if (j)
	{
		j->state = new_state;
	}
}

char *job_state_tostr(t_job_state s)
{
	if (s == STOPPED)
	{
		return ("Stopped");
	}
	if (s == DONE)
	{
		return ("Done");
	}
	return ("Running");
}
