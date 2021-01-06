/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_hash_function.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 22:48:12 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 12:10:26 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hashtable.h"
#include "inc21sh.h"

/*
** Фукнция хэширования
*/

int						hash_api_hash_function(char *key)
{
	unsigned long hash;

	if (key == NULL)
		return (-1);
	hash = 5381;
	while (*key)
	{
		hash = (hash * 33) ^ *key;
		key++;
	}
	hash = hash % HASH_SIZE;
	return ((unsigned int)hash);
}