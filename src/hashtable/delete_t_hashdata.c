/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_delete_hash_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:30:01 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:07:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "inc21sh.h"

void					delete_t_hashdata(t_hashdata **hd)
{
	t_hashtable		*table;
	t_hashtable		*table_prev;
	int				i;

	if (hd == NULL || *hd == NULL)
		return ;
	i = 0;
	table_prev = NULL;
	while (i < HASH_SIZE)
	{
		if ((table = (*hd)->hashtable[i]) != NULL)
		{
			while (table)
			{
				table_prev = table;
				table = table->next;
				delete_hash_table_element(&table_prev);
			}
		}
		i++;
	}
	free(*hd);
}
