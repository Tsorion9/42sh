/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_search.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 19:45:28 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/06 13:02:35 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "gayprompt.h"

/*! \fn history_search_print
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Печать строки поиска по истории \n
 *  \param[in] history_search структура поиска по истории
 *  \param[in] user_in найденная строка из истории 42sh
 *  \param[in] cur_pos позиция курсора после вывода строки поиска
 *  по истории
 *  \param[in] found строка найдена/не найдена
 */
static void	history_search_print(const t_history_search *history_search, const char *user_in, 
	const int *cur_pos, int found)
{
	int		new_cur_pos[2];
	char	*history_search_before;

	if (!(history_search && user_in && history_search->str))
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
	ft_putstr_fd(user_in, STDERR_FILENO);
	inverse_search_index(rp(NULL)->cur_pos, rp(NULL)->len, ft_strlen(history_search_before) +
			ft_strlen(history_search->str) + ft_strlen(HISTORY_SEARCH_STR_AFTER));
	if (rp(NULL)->cur_pos[0] == 1)
	{
		ft_putstr(" \r");
	}
	move_cursor_to_new_position(rp(NULL)->cur_pos, new_cur_pos);
	ft_memcpy(rp(NULL)->cur_pos, new_cur_pos, sizeof(new_cur_pos));
}

/*! \fn history_search
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Устанавливает глобальные переменные
 *  user_in и history в соответствии с поиском \n
 *  \param[out] cur_pos позиция курсора после поиска
 *  \param[in/out] index индекс, с которого ведется поиск
 *  \param[in] history_str строка поиска по истории
 *  в глобальной строке user_in
 *  \return 0 - история не найдена, 1 - история найдена
 */
static int	history_search(int *cur_pos, size_t *index, const char *history_str)
{
	int			found;
	t_history	*history_ptr;
	size_t		search_index;

	found = 0;
	history_ptr = rp(NULL)->history;
	search_index = *index;
	while (history_ptr->next && !found)
	{
		while (!ft_strfirststr(history_ptr->str + search_index, history_str) && search_index)
			search_index = search_index - 1;
		if (search_index == 0 && !ft_strfirststr(history_ptr->str, history_str))
		{
			history_ptr = history_ptr->next;
			search_index = history_ptr->len;
		}
		else
		{
			rp(NULL)->history = history_ptr;
			set_new_user_in(history_ptr->str);
			*index = search_index;
			found = 1;
		}
	}
	if (found)
		inverse_search_index(cur_pos, *index, ft_strlen(HISTORY_SEARCH_STR_BEFORE) +
			ft_strlen(history_str) + ft_strlen(HISTORY_SEARCH_STR_AFTER));
	else
		inverse_search_index(cur_pos, *index, ft_strlen(HISTORY_SEARCH_STR_NOT_FOUND_BEFORE) +
			ft_strlen(history_str) + ft_strlen(HISTORY_SEARCH_STR_AFTER));
	return (found);
}

/*! \fn reset_history_search
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Сбрасывает структуру t_history_search в
 *  начальное положение \n
 *  \param[out] history_search структура поиска истории
 */
static void	reset_history_search(t_history_search *history_search)
{
	history_search->index = 0;
	history_search->history_search_mode = 0;
	history_search->len = 0;
	ft_memset(history_search->str, 0, BUFFSIZE);
}

/*! \fn exit_history_search
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Сбрасывает все параметры перед выходом
 *  из режима поиска по истории \n
 *  \param[in/out] history_search структура поиска истории
 */
static void exit_history_search(t_history_search *history_search)
{
	int	new_cur_pos[2];
	int	prev_cur_pos[2];
	
	ft_memcpy(prev_cur_pos, rp(NULL)->cur_pos, sizeof(prev_cur_pos));
	tc_save_cursor_pos();
	clear_all_line(1);
	rp(NULL)->index = history_search->index;
	inverse_search_index(new_cur_pos, rp(NULL)->index, ft_strlen(rp(NULL)->prompt));
	gayprompt(rp(NULL)->prompt);
	ft_putstr(rp(NULL)->user_in);
	tc_restore_saved_cursor_pos();
	move_cursor_to_new_position(prev_cur_pos, new_cur_pos);
	ft_memcpy(rp(NULL)->cur_pos, prev_cur_pos, sizeof(rp(NULL)->cur_pos));
	reset_history_search(history_search);
}

/*! \fn set_history_search_mode
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Устанавливает параметры перед началом
 *  поиска по истории \n
 *  \param[in/out] history_search структура поиска истории
 */
void		set_history_search_mode()
{
	rp(NULL)->history_search.history_search_mode = 1;
	rp(NULL)->history_search.index = rp(NULL)->index + 1;
}

/*! \fn now_search_history
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Проверяет, установлен ли сейчас режим
 *  поиска по истории \n
 *  \return 0 - не установлен, 1 - установлен
 */
int			now_search_history()
{
	return (rp(NULL)->history_search.history_search_mode);
}

void		history_search_start(long c)
{
	t_history_search	*t_history_search = &(rp(NULL)->history_search);
	int					cur_pos[2] = {1, 1};
	static int			found = 1;
	size_t				prev_index;

	found = 1;
	if (c == LEFT_ARROW || c == RIGHT_ARROW || c == UP_ARROW || c == DOWN_ARROW || 
	c == '\n' || c == CTRL_E || c == UP_ARROW || c == DOWN_ARROW)
	{
		exit_history_search(t_history_search);
		return ;
	}
	else if (is_print(c))
	{
		add_symbol_in_str(t_history_search->str, c, t_history_search->len);
		t_history_search->len++;
		found = history_search(cur_pos, &(t_history_search->index), t_history_search->str);
	}
	else if (c == BACKSPACE && t_history_search->len)
	{
		delete_symbol_in_str(t_history_search->str, t_history_search->len - 1);
		t_history_search->len--;
		found = history_search(cur_pos, &(t_history_search->index), t_history_search->str);
	}
	else if (c == CTRL_R && now_search_history())
	{
		prev_index = t_history_search->index;
		if (t_history_search->index > 0)
			t_history_search->index--;
		else if (rp(NULL)->history->next)
		{
			rp(NULL)->history = rp(NULL)->history->next;
			t_history_search->index = rp(NULL)->history->len;
		}
		found = history_search(cur_pos, &(t_history_search->index), t_history_search->str);
		if (!found)
		{
			t_history_search->index = prev_index;
			ft_memcpy(cur_pos, rp(NULL)->cur_pos, sizeof(rp(NULL)->cur_pos));
		}
	}
	else
	{
		if (found)
			inverse_search_index(cur_pos, t_history_search->index, ft_strlen(HISTORY_SEARCH_STR_BEFORE) +
				t_history_search->len + ft_strlen(HISTORY_SEARCH_STR_AFTER));
		else
			inverse_search_index(cur_pos, t_history_search->index, ft_strlen(HISTORY_SEARCH_STR_NOT_FOUND_BEFORE) +
				t_history_search->len + ft_strlen(HISTORY_SEARCH_STR_AFTER));
	}
	history_search_print(t_history_search, rp(NULL)->user_in, cur_pos, found);
}
