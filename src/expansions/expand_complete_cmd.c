/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_complete_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:38 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "remove_quotes.h"
#include "inc21sh.h"
#include "expand_word.h"
#include "expand_assignment.h"

void		expand_inside_wl(void **p)
{
	*p = expand_word(*p);
}

void		expand_inside_arl(void *p)
{
	t_ar	*ar;
	char	*s;

	ar = (t_ar *)p;
	if (ar->what == assignment)
	{
		s = expand_assignment(ar->data);
		ar->data = s;
	}
	else
		expand_inside_wl(&(((t_io_redir *)(ar->data))->where->content));
}

void		expand_simple_cmd(void *c)
{
	t_simple_cmd	*cmd;

	cmd = (t_simple_cmd *)c;
	if (!cmd)
		return ;
	if (cmd->wl)
		deque_apply_inplace(cmd->wl, expand_inside_wl);
	if (cmd->arl)
		deque_apply(cmd->arl, expand_inside_arl);
}

void		expand_pipeline(void *pipeline)
{
	deque_apply(((t_pipeline *)pipeline)->commands, expand_simple_cmd);
}

void		expand_complete_cmd(t_deque *cmd)
{
	deque_apply(cmd, expand_pipeline);
}
