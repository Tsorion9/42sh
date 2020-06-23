/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_readline_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:45 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:46 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"

static void	back_to_start_history_rp(void)
{
	if (rp()->history)
		while (rp()->history->prev)
			rp()->history = rp()->history->prev;
}

static void	reset_cur_pos_rp(void)
{
	rp()->cur_pos[0] = rp()->prompt_len;
	rp()->cur_pos[1] = 1;
}

void		reset_rp_to_start(char *new_prompt)
{
	if (!(rp()->user_in = (char*)ft_memalloc(sizeof(char) * MIN_CMD_LENGTH)))
		reset_exit(1);
	rp()->max_len = MIN_CMD_LENGTH;
	rp()->len = 0;
	back_to_start_history_rp();
	rp()->prompt_len = ft_strlen(new_prompt) + 1;
	reset_cur_pos_rp();
}
