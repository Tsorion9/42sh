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

/*! \fn history_search_print
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Печать строки поиска по истории \n
 *  \param[in] history_str строка, по которой ведется поиск
 *  \param[in] user_in найденная строка из истории 42sh
 *  \param[in] cur_pos позиция курсора после вывода строки поиска
 *  по истории
 *  \param[in] history_str_len длина строки, по которой ведется поиск
 */
static void	history_search_print(const char *history_str, const char *user_in, const int *cur_pos,
	size_t history_str_len)
{
	size_t	prompt_len;
	int		new_cur_pos[2];

	if (!(history_str && user_in))
		return ;
	ft_memcpy(new_cur_pos, cur_pos, sizeof(new_cur_pos));
	clear_all_line(1);
	ft_putstr_fd(HISTORY_SEARCH_STR_BEFORE, STDERR_FILENO);
	ft_putstr_fd(history_str, STDERR_FILENO);
	ft_putstr_fd(HISTORY_SEARCH_STR_AFTER, STDERR_FILENO);
	ft_putstr_fd(user_in, STDERR_FILENO);
	prompt_len = ft_strlen(HISTORY_SEARCH_STR_BEFORE) + history_str_len +
		ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1;
	cur_pos_after_putstr(rp(NULL)->cur_pos, prompt_len);
	move_cursor_to_new_position(rp(NULL)->cur_pos, new_cur_pos);
}

/*! \fn history_search
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Устанавливает глобальные переменные
 *  user_in и history в соответствии с поиском \n
 *  \param[out] cur_pos позиция курсора после поиска
 *  \param[in/out] index индекс, с которого ведется поиск
 *  \param[in] history_str строка поиска по истории
 *  в глобальной строке user_in
 */
static void	history_search(int *cur_pos, size_t *index, const char *history_str)
{
	int found;

	found = 0;
	while (rp(NULL)->history->next && !found)
	{
		while (!ft_strstr(rp(NULL)->user_in + *index, history_str) && *index)
			*index = *index - 1;
		if (*index == 0 && !ft_strstr(rp(NULL)->user_in, history_str))
		{
			if (rp(NULL)->history->next != NULL)
				rp(NULL)->history = rp(NULL)->history->next;
			set_new_user_in(rp(NULL)->history->str);
			*index = rp(NULL)->len;
		}
		else
			found = 1;
	}
	inverse_search_index(cur_pos, *index, ft_strlen(HISTORY_SEARCH_STR_BEFORE) +
		ft_strlen(history_str) + ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
}

void		history_search_start(long c)
{
	t_history_search	*t_history_search = &(rp(NULL)->history_search);
	int					cur_pos[2] = {1, 1};

	if (is_print(c))
	{
		add_symbol_in_str(t_history_search->str, c, t_history_search->len);
		t_history_search->len++;
		history_search(cur_pos, &(t_history_search->index), t_history_search->str);
	}
	else if (c == BACKSPACE && t_history_search->len)
	{
		delete_symbol_in_str(t_history_search->str, t_history_search->len - 1);
		t_history_search->len--;
		history_search(cur_pos, &(t_history_search->index), t_history_search->str);
	}
	else
	{
		inverse_search_index(cur_pos, rp(NULL)->index, ft_strlen(HISTORY_SEARCH_STR_BEFORE) +
			t_history_search->len + ft_strlen(HISTORY_SEARCH_STR_AFTER) + 1);
	}
	history_search_print(t_history_search->str, rp(NULL)->user_in, cur_pos, t_history_search->len);
	if (c == LEFT_ARROW || c == RIGHT_ARROW)
	{
		t_history_search->history_search_mode = 0;
		t_history_search->len = 0;
		ft_memset(t_history_search->str, 0, BUFFSIZE);
		clear_all_line(1);
	}
}
