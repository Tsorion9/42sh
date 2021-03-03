/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_command_to_hash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:28:31 by nriker            #+#    #+#             */
/*   Updated: 2021/03/02 20:34:44 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			insert_command_to_hash(char *key, char *value)
{
	t_hash			*hash;
	char			*str;

	if ((hash = static_hash_action(get)) == NULL
		|| hash->hd == NULL)
		return ;
	str = NULL;
	if ((str = search_hash(value)) == NULL)
		insert_hash(key, value);
	else
		free(str);
}
