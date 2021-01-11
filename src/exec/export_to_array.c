/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 20:30:28 by nriker            #+#    #+#             */
/*   Updated: 2021/01/11 21:14:31 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

char		*concatenation_key_value(char *key, char *value)
{
	char	*res;
	char	*current;

	res = ft_memalloc(sizeof(char) * (ft_strlen(key) + ft_strlen(value) + 2));
	if (!res)
		return (NULL);
	current = res;
	while ((*current++ = *key++))
		;
	--current;
	*current++ = '=';
	while ((*current++ = *value++))
		;
	return (res);
}

int			array_cycle(t_hashtable *table, char **array, int *i)
{
	while (table)
	{
		if ((array[*i] = concatenation_key_value(table->key,
			table->value)) == NULL)
		{
			if (array)
				del_array(array);
			return (EXIT_FAILURE);
		}
		(*i)++;
		table = table->next;
	}
	return (EXIT_SUCCESS);
}

void		fill_array(t_export *export, char **array)
{
	t_hashtable		*table;
	int				i;
	int				size;

	i = 0;
	size = 0;
	while (size < HASH_SIZE)
	{
		table = export->hd->hashtable[size];
		if (table)
			if (array_cycle(table, array, &i) == EXIT_FAILURE)
				return ;
		size++;
	}
}

char		**export_to_array(void)
{
	t_export		*export;
	char			**array;

	if ((export = static_export_action(get)) == NULL)
		return (NULL);
	if ((array = ft_memalloc(sizeof(char *) * (export->size + 1))) == NULL)
		return (NULL);
	fill_array(export, array);
	return (array);
}