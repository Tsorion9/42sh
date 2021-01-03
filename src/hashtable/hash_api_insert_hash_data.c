/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_insert_hash_data.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 14:33:31 by nriker            #+#    #+#             */
/*   Updated: 2021/01/03 16:14:22 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "hashtable.h"

int						new_hash_table_element(t_hashtable **ht,
							char *key, char *value)
{
	t_hashtable *new;

	new = (t_hashtable*)ft_memalloc(sizeof(t_hashtable));
	if (new == NULL)
		return (EXIT_FAILURE);
	if ((new->key = ft_strdup(key)) == NULL
		|| (new->value = ft_strdup(value)) == NULL)
	{
		free(new);
		return (EXIT_FAILURE);
	}
	*ht = new;
	return (EXIT_SUCCESS);
}

int						hash_api_change_data(t_hashtable **ht, char *value)
{
	if ((*ht)->value)
	{
		free((*ht)->value);
		if (!((*ht)->value = ft_strdup(value)))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int						hash_api_insert_hash_value(char *key, char *value,
							t_hashdata *hd)
{
	int		i;

	i = 0;
	if (hd == NULL)
		return (EXIT_FAILURE);
	i = hash_api_hash_function(key);
	while (hd->hashtable[i] || !ft_strequ(hd->hashtable[i]->key, key))
		hd->hashtable[i] = hd->hashtable[i]->next;
	if (hd->hashtable[i])
	{
		if (hash_api_change_data(&hd->hashtable[i], value))
			return (EXIT_FAILURE);
	}
	else if (new_hash_table_element(&(hd->hashtable[i]), key, value))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
