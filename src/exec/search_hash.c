/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:33:16 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 07:34:22 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

char			*search_hash(char *key)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return (NULL);
	return (search_hash_data(key, hash->hd));
}
