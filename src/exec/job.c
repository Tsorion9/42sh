#include "libft.h"
#include "job.h"

t_list *jobs;

/*
** Create new job if not exists
** Add PID to list of pids if job exists
*/
void add_job(int pgid, int background)
{
	t_job *new;

	new = ft_memalloc(sizeof(t_job));
	new->pgid = pgid;
	new->state = background ? BACKGROUND : FG;
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
	if (delete_me && !prev && jobs) /* Del first */
	{
		prev = jobs;
		jobs = jobs->next;
		ft_lstdelone(&prev, destroy_job);
	}
}

/*
** Find by pgid
*/
t_job *find_job(pid_t pgid)
{
	t_list	*l;
	t_job	*j;

	l = jobs;
	while (l)
	{
		j = (t_job *)l->content;
		if (j->pgid == pgid)
		{
			break;
		}
		l = l->next;
	}
	return (j);
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
