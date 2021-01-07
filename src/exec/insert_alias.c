/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_alias.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:24:48 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:02:11 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void					insert_alias(char *key, char *value)
{
	t_hashalias		*hash_alias;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return ;
	if (value == NULL)
	{
		value = ft_strdup("''");
		insert_hash_value(key, value, hash_alias->hd);
		free(value);
	}
	else
		insert_hash_value(key, value, hash_alias->hd);
}
