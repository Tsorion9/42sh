/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_command_to_hash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:28:31 by nriker            #+#    #+#             */
/*   Updated: 2021/02/22 19:08:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			insert_command_to_hash(char *key, char *value)
{
	t_hash			*hash;
	char			**path_dirs;
	char			*str;

	if ((hash = static_hash_action(get)) == NULL
		|| hash->hd == NULL)
		return ;
	path_dirs = ft_strsplit(ft_getenv(g_env, "PATH"), ':');
	if (is_path_was_changed(hash->copy_path, path_dirs) == EXIT_SUCCESS)
	{
		static_hash_action(del);
		static_hash_action(init);
		if (path_dirs)
			del_array(path_dirs);
		return ;
	}
	str = NULL;
	if (path_dirs)
		del_array(path_dirs);
	if ((str = search_hash(value)) == NULL)
		insert_hash(key, value);
	else
		free(str);
}
