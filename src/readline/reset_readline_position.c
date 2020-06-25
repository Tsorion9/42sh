/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_readline_position.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:45 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 20:08:16 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	reset_cur_pos_rp(void)
{
	rp(NULL)->cur_pos[0] = rp(NULL)->prompt_len;
	rp(NULL)->cur_pos[1] = 1;
}

void		reset_rp_to_start(char *new_prompt)
{
	if (!(rp(NULL)->user_in = (char*)ft_memalloc(MIN_CMD_LENGTH)))
		reset_exit(1);
	rp(NULL)->max_len = MIN_CMD_LENGTH;
	rp(NULL)->len = 0;
	back_to_start_history_rp();
	rp(NULL)->prompt_len = ft_strlen(new_prompt) + 1;
	rp(NULL)->in_readline = 1;
	reset_cur_pos_rp();
}
