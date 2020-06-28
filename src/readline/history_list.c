/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:34 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:35 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

t_history	*create_history(char *str, size_t len)
{
	t_history	*history;

	if (!(history = (t_history*)xmalloc(sizeof(t_history))))
		exit(1);
	history->str = ft_strdup(str);
	history->len = len;
	history->prev = NULL;
	history->next = NULL;
	return (history);
}

void		add_to_start_history(t_history *history, char *str, size_t len)
{
	t_history	*new_history;

	while (history->prev)
		history = history->prev;
	if (ft_strcmp(str, "") == 0 || str[0] == ' ')
		return ;
	if (history->next)
		if (ft_strcmp(str, history->next->str) == 0)
			return ;
	while (history->prev)
		history = history->prev;
	new_history = create_history(str, len);
	if (history->next)
		history->next->prev = new_history;
	new_history->next = history->next;
	new_history->prev = history;
	history->next = new_history;
}
