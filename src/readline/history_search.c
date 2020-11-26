/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:45:28 by mphobos           #+#    #+#             */
/*   Updated: 2020/11/26 19:45:29 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	history_search_print(char *history_search_buf, char *user_in, int *cur_pos)
{
	size_t	prompt_len;
	int		new_cur_pos[2];

	if (!(history_search_buf && user_in))
		return ;
	ft_memcpy(new_cur_pos, cur_pos, sizeof(new_cur_pos));
	clear_all_line(1);
	ft_putstr_fd(HISTORY_SEARCH_STR_BEFORE, STDERR_FILENO);
	ft_putstr_fd(history_search_buf, STDERR_FILENO);
	ft_putstr_fd(HISTORY_SEARCH_STR_AFTER, STDERR_FILENO);
	ft_putstr_fd(user_in, STDERR_FILENO);
	prompt_len = ft_strlen(HISTORY_SEARCH_STR_BEFORE) + ft_strlen(history_search_buf) +
		ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1;
	cur_pos_after_putstr(rp(NULL)->cur_pos, prompt_len);
	move_cursor_to_new_position(rp(NULL)->cur_pos, new_cur_pos);
}

void	history_search(long c)
{
	/*static char *history_search_buf[BUFFSIZE];*/

	if (c)
	{
		int cur_pos[2];
		char *history_search_buf = "";
		inverse_search_index(cur_pos, rp(NULL)->index, ft_strlen(HISTORY_SEARCH_STR_BEFORE) + ft_strlen(history_search_buf) +
			ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
		history_search_print(history_search_buf, rp(NULL)->user_in, cur_pos);
	}
}
