#include "inc21sh.h"
#include  "t_builtin.h"
#include "job.h"

/*
** Return status message
*/
char *killed(t_job *j)
{
	int status;

	if (waitpid(j->pgid, &status, WNOHANG | WUNTRACED) <= 0)
		return (NULL);
	update_job_state(j->pgid, job_status_to_state(status), status);
	if (j->state == DONE)
		return (job_status_tostr(status));
	return (NULL);
}

int			builtin_fg(char **args, t_env env, int subshell)
{
	t_job *j;
	int error;
	char *str_status;

	(void)env;
	(void)subshell;
	error = -1;

	j = find_job_by_pattern(*args ? *args : "%%", &error);
	if (!j)
	{
		if (error == NO_JOB)
			ft_fprintf(STDERR_FILENO, "No such job: %s\n", *args ? *args : "%%");
		if (error == AMBIGOUS_JOB)
			ft_fprintf(STDERR_FILENO, "Ambigous job: %s\n", *args ? *args : "%%");
	}
	else
	{
		if ((str_status = killed(j))) 
		{
			ft_printf("[%d] %-26s %s\n",
				j->jobid,
				str_status,
				j->cmdline);
			free(str_status);
			return (0);
		}
		ft_printf("%s\n", j->cmdline);
		tcsetattr(STDIN_FILENO, TCSANOW, &(j->tmodes));
		tcsetpgrp(STDIN_FILENO, j->pgid);
		kill(-(j->pgid), SIGCONT);
		j->state = FG;
		wait_fg_job(j->pgid);
	}
	return (error + 1);
}
