/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_hashalias.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:56:39 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 10:58:07 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

t_hashalias				*init_t_hashalias(void)
{
	t_hashalias		*hashalias;

	hashalias = ft_memalloc(sizeof(t_hashalias));
	if (hashalias == NULL)
		return (NULL);
	hashalias->hd = init_t_hashdata();
	if (hashalias->hd == NULL)
		return (NULL);
	return (hashalias);
}
