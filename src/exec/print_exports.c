/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exports.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:09:27 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 17:11:58 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void		print_exports(void)
{
	t_export		*export;
	t_hashtable		*table;
	int				i;

	if ((export = static_export_action(get)) == NULL
		|| export->hd == NULL)
		return ;
	i = 0;
	while (i < HASH_SIZE)
	{
		table = export->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				ft_printf("export %s='%s'\n", table->key, table->value);
				table = table->next;
			}
		}
		i++;
	}
}
