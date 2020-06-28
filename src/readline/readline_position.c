/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:18:34 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 20:18:34 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

t_rp		*rp(t_rp *change_rp)
{
	static t_rp	*rp;

	if (!change_rp)
		return (rp);
	else
		rp = change_rp;
	return (NULL);
}

t_rp		*init_rp(void)
{
	t_rp	*rp;

	if (!(rp = (t_rp*)xmalloc(sizeof(t_rp))))
		reset_exit(1);
	rp->len = 0;
	rp->max_len = MIN_CMD_LENGTH;
	rp->history = create_history("", 0);
	rp->ws_col = ret_winsize(0);
	rp->ws_row = ret_winsize(1);
	rp->in_readline = 0;
	return (rp);
}

void		free_rp(void)
{
	free(rp(NULL)->user_in);
	free_history_list(rp(NULL)->history);
	free(rp(NULL));
}
