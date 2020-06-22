#include "21sh.h"
#include "task_context.h"
#include "static_env.h"

static int		need_new_process(t_simple_cmd *cmd)
{
	char		*word;
	t_builtin	b;

	word = pop_front(cmd->wl);
	b = get_builtin(word);
	if (word)
		push_front(&(cmd->wl), (void *)word);
	else
		return (0);
	return (!b);
}

int				ignore_ass_for_builtin(t_simple_cmd *cmd)
{
	char	*word;

	word = deque_n_th(cmd->wl, 0);
	if (!word)
		return (0);
	else if (!ft_strcmp(word, "echo") || !ft_strcmp(word, "env") ||\
		!ft_strcmp(word, "getenv") || !ft_strcmp(word, "setenv") ||\
		!ft_strcmp(word, "unsetenv") || !ft_strcmp(word, "exit"))
		return (0);
	return (1);
}

t_task_context	init_task_context(t_simple_cmd *cmd, int in_pipe,\
		int out_pipe)
{
	t_task_context	task_context;

	task_context.need_child = need_new_process(cmd);
	task_context.in_pipe = in_pipe;
	task_context.out_pipe = out_pipe;
	task_context.need_subshell = 1;
	if (in_pipe == IGNORE_STREAM &&\
		out_pipe == IGNORE_STREAM &&\
		!task_context.need_child)
	{
		task_context.need_subshell = 0;
	}
	if (ignore_ass_for_builtin(cmd))
		task_context.need_subshell = 1;
	return (task_context);
}

void			enter_task_context(t_task_context *task_context)
{
	if (task_context->need_subshell)
		static_env_action(save, NULL);
	task_context->save_0 = dup(0);
	task_context->save_1 = dup(1);
	task_context->save_2 = dup(2);
	if (task_context->in_pipe != IGNORE_STREAM)
	{
		dup2(task_context->in_pipe, 0);
		close(task_context->in_pipe);
	}
	if (task_context->out_pipe != IGNORE_STREAM)
	{
		dup2(task_context->out_pipe, 1);
		close(task_context->out_pipe);
	}
}

/*
** Actually, we enter this function only in case of builltin or unknown command
*/

void			exit_task_context(t_task_context *task_context)
{
	if (task_context->need_subshell)
		static_env_action(restore, NULL);
	dup2(task_context->save_0, 0);
	dup2(task_context->save_1, 1);
	dup2(task_context->save_2, 2);
	if (task_context->in_pipe != IGNORE_STREAM)
		close(task_context->save_0);
	if (task_context->out_pipe != IGNORE_STREAM)
		close(task_context->save_1);
	close(task_context->save_2);
}
