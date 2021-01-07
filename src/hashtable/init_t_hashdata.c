/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_t_hashdata.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:08:56 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 10:58:50 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

t_hashdata				*init_t_hashdata(void)
{
	t_hashdata	*hashdata;

	hashdata = ft_memalloc(sizeof(t_hashdata));
	if (hashdata == NULL)
		return (NULL);
	return (hashdata);
}
