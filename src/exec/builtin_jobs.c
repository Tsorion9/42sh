#include "exec.h"
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

static void remove_done_jobs(void)
{
	t_list	*l;

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

static int count_args(char **args)
{
	int i;

	i = 0;
	while (args && args[i])
	{
		i++;
	}
	return (i);
}

static void print_single_job(t_job *j, int flag_p, int flag_l)
{
	int		status;

	if (waitpid(j->pgid, &status,  WNOHANG | WUNTRACED | WCONTINUED) == -1) /* Job state changed */
	{
		update_job_state(j->pgid, job_status_to_state(status));
	}

	if (flag_p)
		ft_printf("%d\n", j->pgid);
	else if (flag_l)
	{
		ft_printf("[%d]%s %d %s    %s\n",
					j->jobid,
					figure_out_priority(j),
					j->pgid,
					job_state_tostr(j->state),
					j->cmdline);
	}
	else
		ft_printf("[%d]%s %s    %s\n",
					j->jobid,
					figure_out_priority(j),
					job_state_tostr(j->state),
					j->cmdline);

}

static void	print_job_table(int flag_l, int flag_p)
{
	t_list	*l;
	t_job	*j;

	l = jobs;
	while (l)
	{
		j = (t_job *)l->content;
		print_single_job(j, flag_p, flag_l);
		l = l->next;
	}
}

static void print_matching_jobs(char **args, int flag_l, int flag_p)
{
	t_job *j;
	int error;

	while (*args)
	{
		j = find_job_by_pattern(*args, &error);
		if (!j)
		{
			if (error == NO_JOB)
				ft_fprintf(STDERR_FILENO, "No such job: %s\n", *args);
			if (error == AMBIGOUS_JOB)
				ft_fprintf(STDERR_FILENO, "Ambigous job: %s\n", *args);
		}
		else
			print_single_job(j, flag_p, flag_l);
		args++;
	}
}

int			builtin_jobs(char **args, t_env env, int subshell)
{
	int		flag_l;
	int		flag_p;
	int		errors;

	(void)env;
	(void)subshell;
	if (!top_level_shell) 
	{
		return (1);
	}

	if (errors)
	{
		ft_fprintf(STDERR_FILENO, "%s\n", "Usage: jobs [-l|-p] [job_id...]");
		return (1);
	}
	flag_l = 0;
	flag_p = 0;
	if (*args && !ft_strcmp(args[0], "-l"))
	{
		flag_l = 1;
		args++;
	}
	else if (*args && !ft_strcmp(args[0], "-p"))
	{
		flag_p = 1;
		args++;
	}

	if (!args[0])
		print_job_table(flag_l, flag_p);
	else
		print_matching_jobs(args, flag_l, flag_p);
	remove_done_jobs();
	return (0);
}
