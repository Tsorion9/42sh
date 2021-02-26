/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_null_meet_alias.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:53:24 by nriker            #+#    #+#             */
/*   Updated: 2021/02/26 23:55:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void			set_null_meet_alias(void)
{
	t_hashalias		*alias;
	t_hashtable		*table;
	int				i;

	i = 0;
	if ((alias = static_hashalias_action(get)) == NULL
		|| alias->hd == NULL)
		return ;
	while (i < HASH_SIZE)
	{
		table = alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				table->meet_alias = 0;
				table = table->next;
			}
		}
		i++;
	}
}
