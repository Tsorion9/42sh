/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_delete_hash_table.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:02:53 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:09:56 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "hashtable.h"

void					delete_hash_table_element(t_hashtable **table)
{
	if ((*table)->key)
		free((*table)->key);
	if ((*table)->value)
		free((*table)->value);
	erase_tokbuf(&(*table)->tokbuf_value);
	free(*table);
}

t_hashtable				*find_table_prev(t_hashdata *hd, char *key,
							t_hashtable **table, int i)
{
	t_hashtable		*table_prev;

	table_prev = NULL;
	if (((*table) = hd->hashtable[i]) != NULL)
		while ((*table) && ft_strcmp((*table)->key, key))
		{
			if ((*table) && !ft_strcmp((*table)->key, key))
				break ;
			table_prev = (*table);
			(*table) = (*table)->next;
		}
	return (table_prev);
}

int						delete_t_hashtable(char *key, t_hashdata **hd)
{
	int				i;
	t_hashtable		*table;
	t_hashtable		*table_prev;

	i = hash_function(key);
	if (hd == NULL || *hd == NULL || (*hd)->hashtable[i] == NULL)
		return (EXIT_FAILURE);
	table = NULL;
	table_prev = find_table_prev(*hd, key, &table, i);
	if (table == NULL)
		return (EXIT_FAILURE);
	else if (table_prev)
	{
		table_prev->next = table->next;
		delete_hash_table_element(&table);
	}
	else
	{
		table_prev = table->next;
		delete_hash_table_element(&table);
		(*hd)->hashtable[i] = table_prev;
	}
	return (EXIT_SUCCESS);
}
