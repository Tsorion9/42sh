/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_all_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:02 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:03 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Чистит все строки, введенные пользователем.
*/
void		clear_all_line(size_t prompt_len)
{
	if (!prompt_len)
		return ;
	while (rp(NULL)->cur_pos[1] > 1)
		tc_cursor_up();
	while ((size_t)rp(NULL)->cur_pos[0] < prompt_len)
		tc_cursor_right();
	while ((size_t)rp(NULL)->cur_pos[0] > prompt_len)
		tc_cursor_left();
	tc_clear_till_end();
}
