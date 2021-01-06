#include <sys/types.h>
#include <unistd.h>

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "job.h"

/* 
** top-level shell is the only one who does job control
** if top_level_shell==0, we are in job shell
** all our children must stay in same group
*/
int top_level_shell = 1;

/*
** Not used now. Probably, will be helpful for scripts
*/
int job_control_enabled;

/*
** If nonzero, do the asynchronious notification when BG job changes state
** See set -o notify
*/
int async_notify_bg;

/*
** Only top-level shell does the stuff
*/
void sigchld_handler(int n)
{
	pid_t child;
	int status;
	t_job *j;

	child = waitpid(-1, &status,  WNOHANG | WUNTRACED | WCONTINUED);
	if (child == -1) /* Probably, handler was called inside wait() */
	{
		return ;
	}
	j = find_job(child);
	ft_printf("SIGCHLD from: %d\n", child);
	if (WIFSTOPPED(status)) // TODO: use job_status_to_state and job_state_tostr
	{
		update_job_state(child, STOPPED);
		ft_printf("%d Stopped\n", child);
	}
	else if (WIFCONTINUED(status))
	{
		update_job_state(child, BG);
		ft_printf("%d Continued\n", child);
	}
	else if (WIFEXITED(status))
	{
		if (j && j->state != FG) /* TODO: figure out why j can be NULL. Somebody removed it??? */
		{
			ft_printf("%d Terminated\n", child);
		}
		remove_job(child);
	}
	else if (WCOREDUMP(status))
	{
		ft_printf("%d Core dumped\n", child);
		remove_job(child);
	}
	if (j && j->state == FG)
	{
		tcsetpgrp(STDIN_FILENO, getpid());
	}
}

/*
** TRUE = 0
** FALSE = 1
** unlike C language, weird shell stuff
*/
static void update_status(int pipline_status, int *status, t_type_andor last_op)
{
	if (last_op == ANDOR_NONE)
	{
		*status = pipline_status; /* First step */
	}
	else if (last_op == ANDOR_AND)
	{
		*status = *status || pipline_status;
	}
	else if (last_op == ANDOR_OR)
	{
		*status = *status && pipline_status;
	}
}

/*
** Return 1 in case of continue
*/
static int need_exec_pipeline(int status, t_type_andor last_op)
{
	if (last_op == ANDOR_NONE || 
		(last_op == ANDOR_OR && status == 0) || 
		(last_op == ANDOR_AND && status != 0))
	{
		return (1);
	}
	return (0);
}

void set_jobshell_signal(void)
{
	signal(SIGINT, SIG_IGN); /* In case of come child handles */
	signal(SIGTERM, SIG_IGN); /* In case of come child handles */

	/* If SIG_IGN process will be silently destroyed and not turned to zombie*/
	signal(SIGCHLD, SIG_DFL); /* We wait, parent does job control */
	signal(SIGTSTP, SIG_DFL);
}

void perform_word_expansions(t_pipeline *p)
{
	return ;
}

/*
** Return 1
*/
void exec_andor_list(t_andor_list *list, int *status)
{
	int				pipline_status;
	t_type_andor	last_op;

	last_op = ANDOR_NONE;
	while (list)
	{
		if (need_exec_pipeline(*status, last_op))
		{
			perform_word_expansions(list->pipeline); /* Only executed commands should be expanded 
			TODO: Make sure expansions are executed single time
			*/
			pipline_status = exec_pipline(list->pipeline);
			update_status(pipline_status, status, last_op);
		}
		last_op = list->type_andor;
		list = list->next;
	}
}

/*
** Return exit status
*/
int exec_complete_cmd(t_complete_cmd *cmd)
{
	int				status;
	t_complete_cmd	*save_start;
	pid_t			job;

	save_start = cmd;
	while (cmd)
	{
		if (cmd->separator_op == OP_BG) 
		{
			job = fork();
			if (job) /* top-level shell */
			{
				setpgid(job, job);
				add_job(job, 1);
				cmd = cmd->next;
				continue ;
			}
			else	 /* job shell */
			{
				setpgid(getpid(), getpid());
				set_jobshell_signal();
				top_level_shell = 0;
				exec_andor_list(cmd->and_or, &status);
				exit(status);
			}
		}
		exec_andor_list(cmd->and_or, &status);
		cmd = cmd->next;
	}

	clean_complete_command(&save_start);
	return (status);
}
