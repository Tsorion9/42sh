/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:31:00 by nriker            #+#    #+#             */
/*   Updated: 2021/02/22 14:22:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			print_hash(char *key)
{
	char	*hash;

	hash = search_hash(key);
	if (hash)
	{
		ft_printf("hash %s='%s'\n", key, hash);
		free(hash);
	}
}

void			print_all_hash(void)
{
	t_hash			*hash;
	t_hashtable		*table;
	int				i;

	if ((hash = static_hash_action(get)) == NULL
		|| hash->hd == NULL)
		return ;
	i = 0;
	while (i < HASH_SIZE)
	{
		table = hash->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				ft_printf("%s\t\t%s\n", table->key, table->value);
				table = table->next;
			}
		}
		i++;
	}
}
