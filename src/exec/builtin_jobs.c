#include "environment.h"
#include "job.h"

int			builtin_jobs(char **args, t_env env, int subshell)
{
	t_list	*l;
	t_job	*j;
	int		i;

	(void)env;
	(void)subshell;
	(void)args; //TODO: handle -p, and so on, see POSIX

	l = jobs;
	i = 0;
	while (l)
	{
		j = (t_job *)l->content;
		ft_printf("[%d] %d %s\n", i++, j->pgid, job_state_tostr(j->state));
		l = l->next;
	}
}
