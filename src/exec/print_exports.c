/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exports.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:09:27 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 23:19:43 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void		print_export(char *key)
{
	char	*export;

	export = search_export(key);
	if (export)
	{
		ft_printf("export %s=\"%s\"\n", key, export);
		free(export);
	}
}

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
				ft_printf("export %s=\"%s\"\n", table->key, table->value);
				table = table->next;
			}
		}
		i++;
	}
}
