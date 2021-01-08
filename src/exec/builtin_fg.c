#include "inc21sh.h"
#include  "t_builtin.h"
#include "job.h"

int			builtin_fg(char **args, t_env env, int subshell)
{
	t_job *j;
	int error;

	(void)env;
	(void)subshell;
	error = -1;
	if (!*args)
	{
		j = find_job_by_pattern(*args ? *args : "%%", &error);
	}
	if (!j)
	{
		if (error == NO_JOB)
			ft_fprintf(STDERR_FILENO, "No such job: %s\n", *args);
		if (error == AMBIGOUS_JOB)
			ft_fprintf(STDERR_FILENO, "Ambigous job: %s\n", *args);
	}
	else
	{
		ft_printf("%s\n", j->cmdline);
		tcsetattr(STDIN_FILENO, TCSANOW, &(j->tmodes));
		tcsetpgrp(STDIN_FILENO, j->pgid);
		if (j->state == STOPPED)
			kill(j->pgid, SIGCONT);
		j->state = FG;
		wait_fg_job(j->pgid);
	}
	return (error + 1);
}
