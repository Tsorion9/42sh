/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 06:49:07 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 06:52:40 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

t_hash			*init_t_hash(void)
{
	t_hash		*hash;

	hash = ft_memalloc(sizeof(t_hash));
	if (hash == NULL)
		return (NULL);
	hash->hd = init_t_hashdata();
	hash->copy_path = NULL;
	if (hash->hd == NULL)
		return NULL;
	return (hash);
}
