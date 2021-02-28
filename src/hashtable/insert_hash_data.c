/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_hash_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:33:31 by nriker            #+#    #+#             */
/*   Updated: 2021/02/28 11:02:16 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "deque.h"
#include "lexer.h"
#include "parser.h"

t_hashtable				*new_hash_table_element(char *key, char *value)
{
	t_hashtable *new;
	char		*s;

	new = (t_hashtable*)ft_memalloc(sizeof(t_hashtable));
	if (new == NULL)
		return (NULL);
	if ((new->key = ft_strdup(key)) == NULL
		|| (new->value = ft_strdup(value)) == NULL)
	{
		if (new->key)
			free(new->key);
		if (new->value)
			free(new->value);
		free(new);
		return (NULL);
	}
	s = ft_strdup(value);
	if (!ft_isprint(value[ft_strlen(value) - 1])
		|| value[ft_strlen(value) - 1] == ' ')
		new->expand_next_alias = 1;
	new->tokbuf_value = split_word_into_queue_tokens(s);
	free(s);
	return (new);
}

int						hash_api_change_data(t_hashtable **ht, char *value)
{
	char	*s;

	if ((*ht)->value)
	{
		free((*ht)->value);
		if (!((*ht)->value = ft_strdup(value)))
			return (EXIT_FAILURE);
		erase_tokbuf(&(*ht)->tokbuf_value);
		s = ft_strdup((*ht)->value);
		(*ht)->tokbuf_value = split_word_into_queue_tokens(s);
		free(s);
	}
	return (EXIT_SUCCESS);
}

t_hashtable				*find_table_and_table_prev(t_hashdata *hd, char *key,
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

int						find_hash_elements(t_hashtable **table,
							t_hashtable **table_prev, char *key, char *value)
{
	if ((*table) && !ft_strcmp((*table)->key, key))
	{
		if (hash_api_change_data(table, value) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (!(*table) && (*table_prev))
	{
		if (((*table_prev)->next = new_hash_table_element(key, value)) == NULL)
			return (EXIT_FAILURE);
	}
	else if (((*table) = new_hash_table_element(key, value)) == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int						insert_hash_value(char *key, char *value,
							t_hashdata *hd)
{
	int				i;
	t_hashtable		*table;
	t_hashtable		*table_prev;

	if (hd == NULL)
		return (EXIT_FAILURE);
	if ((i = hash_function(key)) == -1)
		return (EXIT_FAILURE);
	table = NULL;
	table_prev = find_table_and_table_prev(hd, key, &table, i);
	if (find_hash_elements(&table, &table_prev, key, value) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (hd->hashtable[i] == NULL)
		hd->hashtable[i] = table;
	if (!(hd->if_has_content))
		hd->if_has_content = 1;
	return (EXIT_SUCCESS);
}
