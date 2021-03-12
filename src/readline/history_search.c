/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:45:28 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/12 13:16:12 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "gayprompt.h"

static void	history_search_print(const t_history_search *history_search,
								const char *user_in, const int *cur_pos,
								int found)
{
	int		new_cur_pos[2];
	char	*history_search_before;

	if (!(history_search && user_in))
		return ;
	ft_memcpy(new_cur_pos, cur_pos, sizeof(new_cur_pos));
	clear_all_line(1);
	if (found)
		history_search_before = HISTORY_SEARCH_STR_BEFORE;
	else
		history_search_before = HISTORY_SEARCH_STR_NOT_FOUND_BEFORE;
	ft_putstr_fd(history_search_before, STDERR_FILENO);
	ft_putstr_fd(history_search->str, STDERR_FILENO);
	ft_putstr_fd(HISTORY_SEARCH_STR_AFTER, STDERR_FILENO);
	readline_putstr(user_in, rp(NULL)->cur_pos,
	ft_strlen(history_search_before) +
	ft_strlen(history_search->str) + ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
	move_cursor_to_new_position(rp(NULL)->cur_pos, new_cur_pos);
	ft_memcpy(rp(NULL)->cur_pos, new_cur_pos, sizeof(new_cur_pos));
}

int			history_search(int *cur_pos, size_t *index, const char *history_str)
{
	int			found;
	t_history	*history_ptr;
	size_t		search_index;

	found = 0;
	history_ptr = rp(NULL)->history;
	search_index = *index;
	while (history_ptr->next && !found)
	{
		while (!ft_strfirststr(history_ptr->str + search_index, history_str) &&
		search_index)
			search_index = search_index - 1;
		if (search_index == 0 && !ft_strfirststr(history_ptr->str, history_str))
		{
			history_ptr = history_ptr->next;
			search_index = history_ptr->len;
		}
		else
			history_search_sup(history_ptr, index, search_index, &found);
	}
	hs_search_index(cur_pos, *index, ft_strlen(history_str), found);
	return (found);
}

static void	reset_history_search(t_history_search *history_search)
{
	history_search->index = 0;
	history_search->history_search_mode = 0;
	history_search->len = 0;
	ft_memset(history_search->str, 0, BUFFSIZE);
}

static void	exit_history_search(t_history_search *history_search)
{
	int	new_cur_pos[2];
	int	prev_cur_pos[2];

	ft_memcpy(prev_cur_pos, rp(NULL)->cur_pos, sizeof(prev_cur_pos));
	tc_save_cursor_pos();
	clear_all_line(1);
	rp(NULL)->index = history_search->index;
	inverse_search_index(new_cur_pos, rp(NULL)->index, rp(NULL)->prompt_len);
	gayprompt(rp(NULL)->prompt);
	ft_putstr(rp(NULL)->user_in);
	tc_restore_saved_cursor_pos();
	move_cursor_to_new_position(prev_cur_pos, new_cur_pos);
	ft_memcpy(rp(NULL)->cur_pos, prev_cur_pos, sizeof(rp(NULL)->cur_pos));
	reset_history_search(history_search);
}

void		history_search_start(long c)
{
	t_history_search	*history_search;
	int					cur_pos[2];
	static int			found = 1;
	size_t				prev_index;

	history_search = &(rp(NULL)->history_search);
	ft_memset(cur_pos, 1, sizeof(cur_pos));
	if (c == LEFT_ARROW || c == RIGHT_ARROW || c == UP_ARROW ||
	c == DOWN_ARROW || c == '\n' || c == CTRL_E || c == UP_ARROW ||
	c == DOWN_ARROW)
	{
		exit_history_search(history_search);
		return ;
	}
	else if (is_print(c))
		hs_add_symbol(history_search, cur_pos, &found, c);
	else if (c == BACKSPACE && history_search->len)
		hs_delete_symbol(history_search, cur_pos, &found);
	else if (c == CTRL_R && now_search_history())
		hs_search_new_history(&prev_index, history_search, cur_pos, &found);
	else
		hs_search_index(cur_pos, history_search->index,
		history_search->len, found);
	history_search_print(history_search, rp(NULL)->user_in, cur_pos, found);
}
