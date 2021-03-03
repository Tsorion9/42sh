/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:05:04 by nriker            #+#    #+#             */
/*   Updated: 2021/03/03 19:22:22 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			insert_hash(char *key, char *value)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return ;
	insert_hash_value(key, value, hash->hd);
}
