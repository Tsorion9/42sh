#include "environment.h"
#include "job.h"

static char *figure_out_priority(t_job *j)
{
	int		max;
	int		second_max;

	biggest_priorities(&max, &second_max);
	if (j->priority == max)
	{
		return ("+");
	}
	if (j->priority == second_max)
	{
		return ("-");
	}
	return (" ");
}

void remove_done_jobs(void)
{
	t_list	*l;
	t_job	*j;

	l = jobs;
	while (l)
	{
		if(((t_job *)l->content)->state == DONE) 
		{
			remove_job(((t_job *)(l->content))->pgid);
			l = jobs;
			continue ;
		}
		l = l->next;
	}
}

int			builtin_jobs(char **args, t_env env, int subshell)
{
	t_list	*l;
	t_job	*j;
	int		i;
	int		status;

	(void)env;
	(void)subshell;
	(void)args; //TODO: handle -p, and so on, see POSIX

	l = jobs;
	i = 0;
	while (l)
	{
		j = (t_job *)l->content;
		if ( waitpid(j->pgid, &status,  WNOHANG | WUNTRACED | WCONTINUED) == -1) /* Job state changed */
		{
			update_job_state(j->pgid, job_status_to_state(status));
		}

		ft_printf("[%d]%s %d %s\n", j->jobid, figure_out_priority(j), j->pgid, job_state_tostr(j->state));
		l = l->next;
	}
	remove_done_jobs();
	return (0);
}
