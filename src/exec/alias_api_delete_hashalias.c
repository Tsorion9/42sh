/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_delete_hashalias.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:42:28 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 13:45:55 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void					alias_api_delete_hashalias(t_hashalias **hash_alias)
{
    if ((*hash_alias)->hd != NULL)
        hash_api_delete_hash_date((&(*hash_alias)->hd));
    free(*hash_alias);
}
