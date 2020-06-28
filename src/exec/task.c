/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:32:48 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:54 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec_utils.h"
#include "make_assignments_redirections.h"
#include "static_env.h"

/*
** Return zero-terminated array of strings assuming the words are held in deque
** cmd->wl
*/

static char	**collect_argwords(t_simple_cmd *cmd)
{
	char	**args;
	int		i;

	i = 0;
	if (!deque_len(cmd->wl))
		return (NULL);
	args = xmalloc(sizeof(char *) * (deque_len(cmd->wl) + 1));
	while ((args[i] = pop_front(cmd->wl)))
		i++;
	free(cmd->wl);
	cmd->wl = NULL;
	return (args);
}

static int	cleanup_(t_simple_cmd *cmd, t_task_context *task_context)
{
	exit_task_context(task_context);
	rm_simple_cmd(cmd);
	return (0);
}

int			task(t_simple_cmd *cmd, t_task_context *task_context)
{
	char		**av;
	int			status;
	t_builtin	builtin;

	enter_task_context(task_context);
	status = make_assignments_redirections(cmd);
	if (status && task_context->need_child)
		exit(1);
	if (status)
		return (1);
	if (deque_len(cmd->wl) == 0)
		return (cleanup_(cmd, task_context));
	av = collect_argwords(cmd);
	if (!av)
		return (1);
	if (!task_context->need_child && (builtin = get_builtin(av[0])))
		status = builtin(av + 1, static_env_action(get, NULL),\
				task_context->need_subshell);
	else
		find_exec(av, static_env_action(get, NULL));
	del_array(av);
	rm_simple_cmd(cmd);
	exit_task_context(task_context);
	return (status);
}
