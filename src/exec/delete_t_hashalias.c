/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_t_hashalias.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:42:28 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:08:05 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void					delete_t_hashalias(void)
{
    t_hashalias		*hash_alias;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return ;
    if (hash_alias->hd != NULL)
        delete_t_hashdata((&(hash_alias->hd)));
    free(hash_alias);
}
