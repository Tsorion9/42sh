#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include "libft.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"
#include "job.h"
#include "jobshell.h"

int status_to_exitcode(int pipeline_status)
{
	if (WIFEXITED(pipeline_status))
		return (WEXITSTATUS(pipeline_status));
	if (WIFSIGNALED(pipeline_status))
		return (WTERMSIG(pipeline_status) + 128);
	if (WIFSTOPPED(pipeline_status))
		return (WSTOPSIG(pipeline_status) + 128);
	return (pipeline_status);
}

/*
** TRUE = 0
** FALSE = 1
** unlike C language, weird shell stuff
*/
static void update_status(int pipeline_status, int *status, t_type_andor last_op)
{
	last_cmd_status = status_to_exitcode(pipeline_status);
	//printf("%d: pipeline_status=%d, transformed to last_cmd_status=%d\n", getpid(), pipeline_status, last_cmd_status);
	fflush(NULL);
	if (last_op == ANDOR_NONE)
	{
		*status = pipeline_status; /* First step */
	}
	else if (last_op == ANDOR_OR)
	{
		*status = *status || pipeline_status;
	}
	else if (last_op == ANDOR_AND)
	{
		*status = *status && pipeline_status;
	}
}

/*
** Return 1 in case of continue
*/
static int need_exec_pipeline(int status, t_type_andor last_op)
{
	if (last_op == ANDOR_NONE || 
		(last_op == ANDOR_AND && status == 0) || 
		(last_op == ANDOR_OR && status != 0))
	{
		return (1);
	}
	return (0);
}

/*
** Used in jobshell.c
*/
void exec_andor_list(t_andor_list *list, int *status)
{
	int				pipeline_status;
	t_type_andor	last_op;

	last_op = ANDOR_NONE;
	while (list)
	{
		if (need_exec_pipeline(*status, last_op))
		{
			pipeline_status = exec_pipeline(list->pipeline);
			update_status(pipeline_status, status, last_op);
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

	save_start = cmd;
	status = 0;
	while (cmd)
	{
		if (cmd->separator_op == OP_BG) 
		{
			create_jobshell(cmd);
		}
		else
		{
			exec_andor_list(cmd->and_or, &status);
		}
		cmd = cmd->next;
	}
	clean_complete_command(&save_start);
	return (status);
}
