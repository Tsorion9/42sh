/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_readline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:08 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:08 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	free_history_list(t_history *history)
{
	if (!history)
		return ;
	while (history->prev)
		history = history->prev;
	while (history->next)
	{
		history = history->next;
		free(history->prev->str);
		free(history->prev);
	}
	free(history->str);
	free(history);
}

void	free_readline_position(void)
{
	free(rp(NULL)->user_in);
	free_history_list(rp(NULL)->history);
	free(rp(NULL));
}
