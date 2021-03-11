/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:18:22 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 01:00:45 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

t_list *g_jobs;

static void	init_locals(char **a, char **b)
{
	*a = NULL;
	*b = NULL;
}

char		*job_status_tostr(int status)
{
	char	*tmp;
	char	*res;

	if (WIFCONTINUED(status))
		return (ft_strdup("Running"));
	if (WCOREDUMP(status))
		return (ft_strdup("Core dumped"));
	init_locals(&tmp, &res);
	if (WIFEXITED(status))
	{
		tmp = ft_itoa(WEXITSTATUS(status));
		res = ft_strjoin("Done:", tmp);
	}
	if (WIFSIGNALED(status))
	{
		tmp = ft_itoa(WTERMSIG(status));
		res = ft_strjoin("Terminated by signal:", tmp);
	}
	if (WIFSTOPPED(status))
	{
		tmp = ft_itoa(WSTOPSIG(status));
		res = ft_strjoin("Stopped by signal:", tmp);
	}
	free(tmp);
	return (res ? res : ft_strdup("Unknown status"));
}

static int	only_digits(char *s)
{
	if (!*s)
		return (0);
	while (*s && ft_isdigit(*s))
	{
		s++;
	}
	return (!(*s));
}

static int	match(t_job *j, char *pattern)
{
	int max;
	int second_max;

	if (*pattern != '%')
		return (0);
	pattern++;
	biggest_priorities(&max, &second_max);
	if (!ft_strcmp(pattern, "+") || !ft_strcmp(pattern, "%"))
		return (j->priority == max);
	if (!ft_strcmp(pattern, "-"))
		return (j->priority == second_max);
	if (only_digits(pattern))
		return (ft_atoi(pattern) == j->jobid);
	if (pattern[0] == '?')
		return (NULL != ft_strstr(j->cmdline, pattern + 1));
	return (!ft_strncmp(j->cmdline, pattern, ft_strlen(pattern)));
}

/*
** Job control patterns (See POSIX)
**
** %%       Current job.
** %+       Current job.
** %-       Previous job.
** %n       Job number n.
** %string  Job whose command begins with string.
** %?string Job whose command contains string.
**
** In case of success return  job
** Error codes: NO_JOB, AMBIGOUS_JOB
*/

t_job		*find_job_by_pattern(char *pattern, int *error)
{
	t_job	*result;
	t_list	*current;

	result = NULL;
	current = g_jobs;
	*error = NO_JOB;
	while (current)
	{
		if (match((t_job *)current->content, pattern))
		{
			if (!result)
				result = (t_job *)current->content;
			else
			{
				*error = AMBIGOUS_JOB;
				return (NULL);
			}
		}
		current = current->next;
	}
	return (result);
}
