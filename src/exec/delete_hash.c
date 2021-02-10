/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:36:55 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 07:41:22 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

int				delete_hash(char *key)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return (EXIT_FAILURE);
	if ((delete_t_hashtable(key, &(hash->hd))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
