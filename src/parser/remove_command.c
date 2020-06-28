/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:27 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "deque.h"
#include "libft.h"
#include "del_inside_wl.h"

void	rm_redir(t_io_redir *redir)
{
	if (!redir)
		return ;
	ft_lstdel(&(redir->where), del_inside_wl);
	free(redir);
}

void	rm_ar(void *p)
{
	t_ar *ar;

	ar = (t_ar *)p;
	if (ar->what == assignment)
		free(ar->data);
	else
		rm_redir((t_io_redir *)ar->data);
	free(ar);
}

void	rm_simple_cmd(void *command)
{
	t_simple_cmd *cmd;

	cmd = (t_simple_cmd *)command;
	deque_del(&(cmd->wl), rm_word);
	deque_del(&(cmd->arl), rm_ar);
	free(cmd);
	return ;
}

void	rm_pipeline(void *pipeline)
{
	t_deque		*commands;
	t_pipeline	*pl;

	pl = (t_pipeline *)pipeline;
	commands = pl->commands;
	deque_del(&commands, rm_simple_cmd);
	free(pl);
	return ;
}

void	rm_compl_cmd(t_deque **command)
{
	deque_del(command, rm_pipeline);
}
