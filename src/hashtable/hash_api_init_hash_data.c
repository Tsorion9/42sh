/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_init_hash_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:08:56 by nriker            #+#    #+#             */
/*   Updated: 2021/01/03 20:36:40 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashdata				*hash_api_init_hash_data(void)
{
	t_hashdata	*hashdata;

	hashdata = ft_memalloc(sizeof(t_hashdata));
	if (hashdata == NULL)
		return (NULL);
	ft_memset(hashdata, 0, HASH_SIZE);
	return (hashdata);
}