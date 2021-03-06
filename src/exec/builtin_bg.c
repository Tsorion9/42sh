#include "t_builtin.h"
#include "job.h"
#include <signal.h>

static void	bg_noargs(int *error)
{
	t_job	*j;

	j = find_job_by_pattern("%%", error);
	if (j)
	{
		kill(j->pgid, SIGCONT);
		j->state = BACKGROUND;
		update_job_priority(j->pgid);
		ft_printf("%s\n", j->cmdline);
	}
	else
	{
		ft_fprintf(STDERR_FILENO, "No such job: Current job\n");
	}
}

static void	handle_no_job_case(int *any_errors, int error, char *arg)
{
	(*any_errors)++;
	if (error == NO_JOB)
		ft_fprintf(STDERR_FILENO, "No such job: %s\n", arg);
	if (error == AMBIGOUS_JOB)
		ft_fprintf(STDERR_FILENO, "Ambigous job: %s\n", arg);
}

int			builtin_bg(char **args, t_env env, int subshell)
{
	int		error;
	t_job	*j;
	int		any_errors;

	(void)env;
	(void)subshell;
	any_errors = 0;
	if (!*args)
		bg_noargs(&any_errors);
	while (*args)
	{
		j = find_job_by_pattern(*args, &error);
		if (!j)
			handle_no_job_case(&any_errors, error, *args);
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
