/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pipeline_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:24:01 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 22:24:02 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	join_pipeline(char **res_cmd, char **cmd_str, t_pipeline *next)
{
	if (*res_cmd == NULL)
	{
		if (next != NULL)
			*res_cmd = ft_strjoinfreefree(*cmd_str, ft_strdup(" | "));
		else
			*res_cmd = *cmd_str;
	}
	else
	{
		*res_cmd = ft_strjoinfreefree(*res_cmd, *cmd_str);
		if (next != NULL)
			*res_cmd = ft_strjoinfreefree(*res_cmd, ft_strdup(" | "));
	}
}

/*
** Return xmalloc string representation of pipeline
** Input: ls >file 123>along arg1 arg2
** Output: ls arg1 arg2 0> file 123> along
*/

char		*get_pipeline_str(t_pipeline *pipeline)
{
	char		*cmd_str;
	char		*res_cmd_str;
	t_command	*cmd;
	t_pipeline	*tmp;

	res_cmd_str = NULL;
	tmp = pipeline;
	while (tmp)
	{
		cmd = tmp->command;
		if (cmd->cmd_type == SIMPLE_CMD)
			cmd_str = simple_cmd_str(cmd->simple_cmd);
		else if (cmd->cmd_type == SUBSHELL)
			cmd_str = subshell_cmd_str(cmd->subshell);
		else if (cmd->cmd_type == BRACE_GROUP)
			cmd_str = brace_group_cmd_str(cmd->brace_group);
		join_pipeline(&res_cmd_str, &cmd_str, tmp->next);
		tmp = tmp->next;
	}
	return (res_cmd_str);
}
