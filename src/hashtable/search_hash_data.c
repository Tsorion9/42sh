/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_get_hash_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:51:42 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:03:17 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"

char					*search_hash_data(char *key, t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;

	if (hd == NULL)
		return (NULL);
	if ((i = hash_function(key)) < 0)
		return (NULL);
	if ((table = hd->hashtable[i]) != NULL)
		while (table && ft_strcmp(table->key, key))
		{
			if (table && !ft_strcmp(table->key, key))
				break ;
			table = table->next;
		}
	if (table == NULL)
		return (NULL);
	return (ft_strdup(table->value));
}
