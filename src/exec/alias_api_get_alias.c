/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_get_alias.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 10:59:47 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 12:05:37 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

char					*alias_api_get_alias(char *key)
{
	t_hashalias		*hash_alias;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return (NULL);
	return (hash_api_get_hash_data(key, hash_alias->hd));
}
