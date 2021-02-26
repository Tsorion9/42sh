/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_first_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 00:14:42 by nriker            #+#    #+#             */
/*   Updated: 2021/02/27 00:15:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void			delete_first_token(t_deque **tokbuf_g)
{
	t_token *del;

	del = pop_front(*tokbuf_g);
	free(del->value);
	free(del);
}
