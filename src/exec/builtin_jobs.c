#include "environment.h"
#include "job.h"

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

		ft_printf("[%d] %d %s\n", j->jobid, j->pgid, job_state_tostr(j->state));
		if (j->state == DONE)
		{
			l = l->next;
			remove_job(j->pgid);
			continue ;
		}
		l = l->next;
	}
}
