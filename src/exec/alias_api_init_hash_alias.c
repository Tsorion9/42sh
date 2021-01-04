/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_init_hash_alias.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:56:39 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 00:43:59 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

t_hashalias				*alias_api_init_hash_alias(void)
{
	t_hashalias		*hashalias;

	hashalias = ft_memalloc(sizeof(t_hashalias));
	if (hashalias == NULL)
		return (NULL);
	hashalias->hd = hash_api_init_hash_data();
	if (hashalias->hd == NULL)
		return NULL;
	return (hashalias);
}
