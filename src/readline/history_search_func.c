/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search_func.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:37:38 by mphobos           #+#    #+#             */
/*   Updated: 2021/03/08 11:37:50 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	history_search_sup(t_history *history_ptr, size_t *index,
	size_t search_index, int *found)
{
	rp(NULL)->history = history_ptr;
	set_new_user_in(history_ptr->str);
	*index = search_index;
	*found = 1;
}

void	hs_delete_symbol(t_history_search *history_search_s, int *cur_pos,
	int *found)
{
	delete_symbol_in_str(history_search_s->str, history_search_s->len - 1);
	history_search_s->len--;
	*found = history_search(cur_pos, &(history_search_s->index),
	history_search_s->str);
}

void	hs_add_symbol(t_history_search *history_search_s, int *cur_pos,
	int *found, long c)
{
	if (history_search_s->len < BUFFSIZE)
	{
		add_symbol_in_str(history_search_s->str, c, history_search_s->len);
		history_search_s->len++;
	}
	*found = history_search(cur_pos, &(history_search_s->index),
	history_search_s->str);
}

void	hs_search_new_history(size_t *prev_index,
	t_history_search *history_search_s, int *cur_pos, int *found)
{
	*prev_index = history_search_s->index;
	if (history_search_s->index > 0)
		history_search_s->index--;
	else if (rp(NULL)->history->next)
	{
		rp(NULL)->history = rp(NULL)->history->next;
		history_search_s->index = rp(NULL)->history->len;
	}
	*found = history_search(cur_pos, &(history_search_s->index),
	history_search_s->str);
	if (!(*found))
	{
		history_search_s->index = *prev_index;
		ft_memcpy(cur_pos, rp(NULL)->cur_pos, sizeof(rp(NULL)->cur_pos));
	}
}

void	hs_search_index(int *cur_pos, size_t index, size_t len, int found)
{
	if (found)
		inverse_search_index(cur_pos, index,
		ft_strlen(HISTORY_SEARCH_STR_BEFORE) +
		len + ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
	else
		inverse_search_index(cur_pos, index,
		ft_strlen(HISTORY_SEARCH_STR_NOT_FOUND_BEFORE) +
		len + ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
}
