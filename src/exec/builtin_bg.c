#include "t_builtin.h"
#include "job.h"
#include <signal.h>

int			builtin_bg(char **args, t_env env, int subshell)
{
	int error;
	t_job *j;
	int any_errors;

	(void)env;
	(void)subshell;
	any_errors = 0;
	if (!*args)
	{
		j = find_job_by_pattern("%%", &error);
		if (j)
		{
			kill(j->pgid, SIGCONT);
			j->state = BACKGROUND;
			update_job_priority(j->pgid);
			ft_printf("%s\n", j->cmdline);
		}
	}
	while (*args)
	{
		j = find_job_by_pattern(*args, &error);
		if (!j)
		{
			any_errors++;
			if (error == NO_JOB)
				ft_fprintf(STDERR_FILENO, "No such job: %s\n", *args);
			if (error == AMBIGOUS_JOB)
				ft_fprintf(STDERR_FILENO, "Ambigous job: %s\n", *args);
		}
		else
		{
			kill(j->pgid, SIGCONT);
			j->state = BACKGROUND;
			update_job_priority(j->pgid);
			ft_printf("%s\n", j->cmdline);
		}
		args++;
	}
	return (any_errors);
}
