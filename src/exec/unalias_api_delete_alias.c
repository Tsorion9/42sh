/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unalias_api_delete_alias.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:26:45 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 13:32:13 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int						unalias_api_delete_alias(t_hashalias **hash_alias, char *key)
{
	if ((hash_api_delete_hash_table(key, &((*hash_alias)->hd))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
