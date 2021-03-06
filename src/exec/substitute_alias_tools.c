/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substitute_alias_tools.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 00:18:19 by nriker            #+#    #+#             */
/*   Updated: 2021/02/28 16:08:49 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void			flush_tokbuf_back(t_deque **destination, t_deque *src)
{
	t_token *tail_token;

	while (src && src->first && src->last)
	{
		tail_token = pop_front(src);
		if (!tail_token)
			return ;
		push_back(destination, tail_token);
	}
}
