/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline_position.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:18:34 by anton             #+#    #+#             */
/*   Updated: 2020/12/01 20:51:34 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		reset_exit(int status);

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
	rp->prompt = NULL;
	rp->user_in = NULL;
	rp->len = 0;
	rp->max_len = MIN_CMD_LENGTH;
	rp->index = 0;
	rp->history = create_history("", 0);
	rp->ws_col = ret_winsize(0);
	rp->ws_row = ret_winsize(1);
	rp->in_readline = 0;
	rp->history_search.history_search_mode = 0;
	return (rp);
}

void		free_rp(void)
{
	if (rp(NULL)->prompt)
		free(rp(NULL)->prompt);
	if (rp(NULL)->user_in)
		free(rp(NULL)->user_in);
	free_history_list(rp(NULL)->history);
	if (rp(NULL))
		free(rp(NULL));
}
