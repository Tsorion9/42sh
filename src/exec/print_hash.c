/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:31:00 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 08:53:52 by nriker           ###   ########.fr       */
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
	int				j;

	if ((hash = static_hash_action(get)) == NULL
		|| hash->hd == NULL)
		return ;
	i = 0;
	j = 0;
	while (i < HASH_SIZE)
	{
		table = hash->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				j++;
				ft_printf("%d\t\t%s\n", j, table->value);
				table = table->next;
			}
		}
		i++;
	}
}
