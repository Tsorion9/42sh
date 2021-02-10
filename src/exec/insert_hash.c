/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_hash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:05:04 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 07:29:58 by nriker           ###   ########.fr       */
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

void			insert_hash_path(char **path)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return ;
	if (hash->copy_path != NULL)
		delete_path();
	hash->copy_path = path;
}
