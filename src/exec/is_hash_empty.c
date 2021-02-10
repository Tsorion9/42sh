/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_hash_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 08:45:40 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 08:49:44 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

int				is_hash_empty(void)
{
	int				i;
	t_hash			*hash;
	t_hashtable		*table;

	if ((hash = static_hash_action(get)) == NULL)
		return (EXIT_SUCCESS);
	i = 0;
	while (i < HASH_SIZE)
	{
		table = hash->hd->hashtable[i];
		if (table)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
