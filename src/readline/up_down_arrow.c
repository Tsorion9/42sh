/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   up_down_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:38 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:14:38 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	up_down_arrow_sup(void)
{
	size_t	lenh;

	clear_all_line();
	lenh = rp(NULL)->history->len / MIN_CMD_LENGTH;
	rp(NULL)->max_len = MIN_CMD_LENGTH * (lenh + 1);
	free(rp(NULL)->user_in);
	if (!(rp(NULL)->user_in = (char*)xmalloc(sizeof(char) * rp(NULL)->max_len)))
		reset_exit(1);
	ft_strcpy(rp(NULL)->user_in, rp(NULL)->history->str);
	ft_putstr_fd(rp(NULL)->user_in, STDERR_FILENO);
	rp(NULL)->len = ft_strlen(rp(NULL)->user_in);
	cur_pos_after_putstr(rp(NULL)->cur_pos);
}

void		up_down_arrow(long c)
{
	if (ft_strcmp(rp(NULL)->user_in, rp(NULL)->history->str))
	{
		free(rp(NULL)->history->str);
		rp(NULL)->history->str = ft_strdup(rp(NULL)->user_in);
		rp(NULL)->history->len = ft_strlen(rp(NULL)->history->str);
	}
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
