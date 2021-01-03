/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_init_hash_data.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:08:56 by nriker            #+#    #+#             */
/*   Updated: 2021/01/03 16:06:19 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashdata				*hash_api_init_hashdata_data(void)
{
	t_hashdata	*hashdata;

	hashdata = ft_memalloc(sizeof(t_hashdata));
	if (hashdata == NULL)
		return (NULL);
	return (hashdata);
}
