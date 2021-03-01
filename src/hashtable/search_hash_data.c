/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_hash_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 21:51:42 by nriker            #+#    #+#             */
/*   Updated: 2021/02/28 11:36:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "deque.h"

t_deque					*search_queue(char *key, t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;

	if (hd == NULL || key == NULL)
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
	return (table->tokbuf_value);
}

char					*search_hash_data_1(char *key, t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;

	if (hd == NULL || key == NULL)
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
	if (!table || !table->tokbuf_value || !table->tokbuf_value->first ||
			!table->tokbuf_value->first->token ||
			!table->tokbuf_value->first->token->value)
		return (NULL);
	return (ft_strdup(table->tokbuf_value->first->token->value));
}

t_hashtable				*search_hash_element(char *key, t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;

	if (hd == NULL || key == NULL)
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
	return (table);
}

char					*search_hash_data(char *key, t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;

	if (hd == NULL || key == NULL)
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
