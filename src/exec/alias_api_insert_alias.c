/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_insert_alias.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 12:24:48 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 12:30:37 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void					alias_api_insert_alias(t_hashalias *hash_alias,
							char *key, char *value)
{
	if (value == NULL)
	{
		value = ft_strdup("''");
		hash_api_insert_hash_value(key, value, hash_alias->hd);
		free(value);
	}
	else
		hash_api_insert_hash_value(key, value, hash_alias->hd);
}
