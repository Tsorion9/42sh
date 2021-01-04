/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_print_all_aliases.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:53:42 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 00:40:28 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hashalias.h"
#include "hashtable.h"

void		alias_api_print_all_aliases(t_hashalias *hash_alias)
{
	print_table(hash_alias->hd);
}
