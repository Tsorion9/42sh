#include "job.h"

t_list *jobs;

/*
** Create new job if not exists
** Add PID to list of pids if job exists
*/
void add_job(int pgid, int background)
{
	int added;
	t_job *new;

	new = malloc(sizeof(t_job));
	new->pgid = pgid;
	new->state = background ? BACKGROUND : FG;
	ft_lstadd_data(&jobs, new, 0);
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
