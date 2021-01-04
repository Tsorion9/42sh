/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_print_hash_table.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 15:45:14 by nriker            #+#    #+#             */
/*   Updated: 2021/01/04 17:53:31 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "gayprompt.h"

void				print_table(t_hashdata *hd)
{
	t_hashtable		*table;
	int				i;

	i = 0;
	while (i < HASH_SIZE)
	{
		// ft_printf("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%d\n", i);
		table = hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				ft_printf("%s=%s\n", table->key, table->value);
				table = table->next;
			}
		}
		// else
		// 	ft_printf("NULL\n");
		i++;
	}
}

void				hash_api_print_hash_table(t_hashdata *hd)
{
    com_api_move_curs_to_end_line();
    ft_putchar('\n');
	print_table(hd);
    gayprompt(rp(NULL)->prompt);
    readline_putstr(rp(NULL)->user_in, rp(NULL)->cur_pos, rp(NULL)->prompt_len);
	com_api_move_curs_to_prev_pos();
}
