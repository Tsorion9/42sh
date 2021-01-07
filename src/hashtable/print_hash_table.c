/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:45:14 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:15:01 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

void				print_table(t_hashdata *hd)
{
	t_hashtable		*table;
	int				i;

	i = 0;
	while (i < HASH_SIZE)
	{
		table = hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				ft_printf("%s=%s\n", table->key, table->value);
				table = table->next;
			}
		}
		i++;
	}
}

void				print_hash_table(t_hashdata *hd)
{
	if (hd == NULL)
		return ;
	com_api_move_curs_to_end_line();
	ft_putchar('\n');
	print_table(hd);
}
