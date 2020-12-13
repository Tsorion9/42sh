/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:38 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/04 20:06:55 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void		reset_exit(int status);

static void	up_down_arrow_sup(void)
{
	set_new_user_in(rp(NULL)->history->str);
	clear_all_line(rp(NULL)->prompt_len);
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
	cur_pos_after_putstr(rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	if (rp(NULL)->cur_pos[0] - 1 == rp(NULL)->ws_col)
	{
		rp(NULL)->cur_pos[0] = 1;
		rp(NULL)->cur_pos[1]++;
		write(STDERR_FILENO, " \r", 2);
	}
}

/*! \fn save_user_in_history
 *  \b Компонента  \b : readline \n
 *  \b Назначение  \b : Устанавливает строку с историей равной 
 *  глобальной строке user_in \n
 */
void		save_user_in_history(void)
{
	if (ft_strcmp(rp(NULL)->user_in, rp(NULL)->history->str))
	{
		free(rp(NULL)->history->str);
		rp(NULL)->history->str = ft_strdup(rp(NULL)->user_in);
		if (!rp(NULL)->history->str)
			reset_exit(1);
		rp(NULL)->history->len = ft_strlen(rp(NULL)->history->str);
	}
}

void		up_down_arrow(long c)
{
	save_user_in_history();
	if (c == UP_ARROW && rp(NULL)->history->next != NULL)
	{
		rp(NULL)->history = rp(NULL)->history->next;
		up_down_arrow_sup();
	}
	else if (c == DOWN_ARROW && rp(NULL)->history->prev != NULL)
	{
		rp(NULL)->history = rp(NULL)->history->prev;
		up_down_arrow_sup();
	}
}
