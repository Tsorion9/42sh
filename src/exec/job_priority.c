#include "job.h"

int		next_priority(void)
{
	static int	priority;

	priority++;
	return (priority);
}

void	update_job_priority(pid_t j)
{
	t_job	*job;

	job = find_job(j);
	if (job)
	{
		job->priority = next_priority();
	}
}

/*
** Set numbers of maximum and second maximum priority
*/

void	biggest_priorities(int *max, int *second_max)
{
	t_job	*j;
	t_list	*l;

	*max = -1;
	*second_max = -1;
	l = g_jobs;
	while (l)
	{
		j = (t_job *)(l->content);
		if (j->priority > *max)
		{
			if (ft_lstlen(g_jobs) > 1)
			{
				*second_max = *max;
			}
			*max = j->priority;
		}
		else if (j->priority > *second_max && ft_lstlen(g_jobs) > 1)
		{
			*second_max = j->priority;
		}
		l = l->next;
	}
}
