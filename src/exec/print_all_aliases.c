/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_aliases.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 22:45:09 by nriker            #+#    #+#             */
/*   Updated: 2021/01/09 22:45:11 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hashalias.h"

void		print_alias(char *key)
{
	char	*alias;

	alias = search_alias(key);
	if (alias)
	{
		ft_printf("alias %s='%s'\n", key, alias);
		free(alias);
	}
}

void		print_all_aliases(void)
{
	t_hashalias		*hash_alias;
	t_hashtable		*table;
	int				i;

	if ((hash_alias = static_hashalias_action(get)) == NULL
		|| hash_alias->hd == NULL)
		return ;
	i = 0;
	while (i < HASH_SIZE)
	{
		table = hash_alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				ft_printf("alias %s='%s'\n", table->key, table->value);
				table = table->next;
			}
		}
		i++;
	}
}
