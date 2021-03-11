#include "job.h"

void	destroy_job(void *j, size_t content_size)
{
	(void)content_size;
	free(((t_job *)j)->cmdline);
	free((t_job *)j);
}

void	remove_job(int pgid)
{
	t_job	*delete_me;
	t_list	*prev;
	t_list	*tmp;

	delete_me = find_job(pgid);
	if (delete_me == g_jobs->content)
	{
		prev = g_jobs;
		g_jobs = g_jobs->next;
		ft_lstdelone(&prev, destroy_job);
	}
	prev = g_jobs;
	while (prev)
	{
		if (prev->next && (prev->next->content == delete_me))
			break ;
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

void	remove_done_jobs(void)
{
	t_list	*l;

	l = g_jobs;
	while (l)
	{
		if (((t_job *)l->content)->state == DONE)
		{
			remove_job(((t_job *)(l->content))->pgid);
			l = g_jobs;
			continue ;
		}
		l = l->next;
	}
}
