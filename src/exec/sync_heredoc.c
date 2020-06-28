/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_heredoc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:46 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:54 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "inc21sh.h"

static int		is_heredoc(t_ar *ar)
{
	t_io_redir	*redir;

	if (ar->what == assignment)
		return (0);
	redir = ar->data;
	return (redir->operation == dless);
}

int				n_heredocs(const t_simple_cmd *cmd)
{
	int	n;
	int	len;
	int	result;

	len = deque_len(cmd->arl);
	n = 0;
	result = 0;
	while (n < len)
	{
		result += is_heredoc((t_ar *)deque_n_th(cmd->arl, n));
		n++;
	}
	return (result);
}

/*
** Delete needed number of elements in the parent here document queue
*/

void			sync_parent_heredoc_state(int child_used)
{
	int	*fd;

	while (child_used--)
	{
		fd = heredoc_action(pop_fd, 0);
		free(fd);
	}
}
