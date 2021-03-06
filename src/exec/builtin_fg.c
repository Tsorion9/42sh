#include "inc21sh.h"
#include "t_builtin.h"
#include "job.h"

/*
** Return status message
*/
static char	*killed(t_job *j)
{
	int status;

	if (waitpid(j->pgid, &status, WNOHANG | WUNTRACED) <= 0)
		return (NULL);
	update_job_state(j->pgid, job_status_to_state(status), status);
	if (j->state == DONE)
		return (job_status_tostr(status));
	return (NULL);
}

static void	move_job_to_fg(t_job *j)
{
	ft_printf("%s\n", j->cmdline);
	tcsetattr(STDIN_FILENO, TCSANOW, &(j->tmodes));
	tcsetpgrp(STDIN_FILENO, j->pgid);
	kill(-(j->pgid), SIGCONT);
	j->state = FG;
	wait_fg_job(j->pgid);
}

static void	handle_error(int error, char *name)
{
	if (error == NO_JOB)
		ft_fprintf(2, "No such job: %s\n", name ? name : "%%");
	if (error == AMBIGOUS_JOB)
		ft_fprintf(2, "Ambigous job: %s\n", name ? name : "%%");
}

int			builtin_fg(char **args, t_env env, int subshell)
{
	t_job	*j;
	int		error;
	char	*str_status;

	(void)env;
	(void)subshell;
	error = -1;
	j = find_job_by_pattern(*args ? *args : "%%", &error);
	if (!j)
	{
		handle_error(error, *args);
	}
	else
	{
		if ((str_status = killed(j)))
		{
			ft_printf("[%d] %-26s %s\n", j->jobid, str_status, j->cmdline);
			free(str_status);
			return (0);
		}
		move_job_to_fg(j);
	}
	return (error + 1);
}
