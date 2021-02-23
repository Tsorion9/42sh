/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:59:47 by nriker            #+#    #+#             */
/*   Updated: 2021/02/24 00:26:54 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"
#include "deque.h"

t_deque					*search_tokbuf(char *key)
{
	t_hashalias		*hash_alias;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return (NULL);
	return (search_queue(key, hash_alias->hd));
}

t_hashtable				*get_hashtable_by_key(char *key, char *value)
{
	t_hashalias		*hash_alias;
	t_hashtable		*table;
	int				i;

	i = 0;
	if ((hash_alias = static_hashalias_action(get)) == NULL
		|| hash_alias->hd == NULL)
		return (NULL);
	while (i < HASH_SIZE)
	{
		table = hash_alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				if (!ft_strcmp(table->value, value))
				{
					return (table);
				}
				table = table->next;
			}
		}
		i++;
	}
	return (NULL);
}

t_deque					*check_tokbuf(char *key, char *value)
{
	t_hashalias		*hash_alias;
	t_hashtable		*table;
	int				i;

	i = 0;
	// ft_printf("check_tokbuf value: %s\n", *value);
	if ((hash_alias = static_hashalias_action(get)) == NULL
		|| hash_alias->hd == NULL)
		return (NULL);
	while (i < HASH_SIZE)
	{
		table = hash_alias->hd->hashtable[i];
		if (table)
		{
			while (table)
			{
				if (!ft_strcmp(table->key, value))
				{
					return (table->tokbuf_value);
				}
				table = table->next;
			}
		}
		i++;
	}
	// ft_printf("check_tokbuf: null\n");
	return (NULL);
}

// char					*check_tok_buf(char *key, char *value, char **copy_key)
// {
// 	t_hashalias		*hash_alias;
// 	t_hashtable		*table;
// 	t_hashtable		*remember_me;
// 	int				i;

// 	i = 0;
// 	remember_me = get_hashtable_by_key(key, value);
// 	// queue = search_tokbuf(key);
// 	if ((hash_alias = static_hashalias_action(get)) == NULL
// 		|| hash_alias->hd == NULL)
// 		return (NULL);
// 	while (i < HASH_SIZE)
// 	{
// 		table = hash_alias->hd->hashtable[i];
// 		if (table)
// 		{
// 			while (table)
// 			{
// 				if (!ft_strcmp(table->key, value))
// 				{
// 					// erase_tokbuf(remember_me->tokbuf_value);
// 					erase_tokbuf(&(remember_me->tokbuf_value));
// 					remember_me->tokbuf_value = deque_copy(table->tokbuf_value);
// 					// *copy_key = table->key;
// 					return (ft_strdup(table->value));
// 					// insert_alias(table->key, value);
// 				}
// 				table = table->next;
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }

char					*search_alias_1(char *key)
{
	t_hashalias		*hash_alias;
	char			*second_value;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return (NULL);
	return (search_hash_data_1(key, hash_alias->hd));
}

char					*search_alias(char *key)
{
	t_hashalias		*hash_alias;
	char			*second_value;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return (NULL);
	return (search_hash_data(key, hash_alias->hd));
}
