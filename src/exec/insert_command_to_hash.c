/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_command_to_hash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:28:31 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 09:39:26 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			insert_command_to_hash(char **path, char *command)
{
	t_hash			*hash;

	if ((hash = static_hash_action(get)) == NULL
		|| hash->hd == NULL)
		return ;
	if (is_path_was_changed(hash->copy_path, path) == EXIT_SUCCESS)
	{
		static_hash_action(del);
		static_hash_action(init);
		return ;
	}
	if (search_hash(command) == NULL)
		insert_hash(command, );
}
