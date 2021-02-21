/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_command_to_hash.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 09:28:31 by nriker            #+#    #+#             */
/*   Updated: 2021/02/19 07:47:04 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			insert_command_value(char **path_dirs,
								char *name_key, char *command_value)
{
	char	*str;

	str = NULL;
	if (path_dirs)
		del_array(path_dirs);
	if ((str = search_hash(command_value)) == NULL)
		insert_hash(name_key, command_value);
	else
		free(str);
}

void			insert_command_to_hash(char *name_key, char *command_value)
{
	t_hash			*hash;
	char			*env_path;
	char			**path_dirs;

	// if ((hash = static_hash_action(get)) == NULL
	// 	|| hash->hd == NULL)
	// {
	// 	insert_hash("test", "1/2/3");
	// 	return ;
	// }
	// insert_hash("test", "1/2/3");
	// insert_hash(name_key, command_value);
	// return ;
	env_path = ft_getenv(env, "PATH");
	path_dirs = ft_strsplit(env_path, ':');
	if (env_path)
		free(env_path);
	env_path = NULL;
	if (is_path_was_changed(hash->copy_path, path_dirs) == EXIT_SUCCESS)
	{
		if (hash->copy_path)
			del_array(hash->copy_path);
		hash->copy_path = NULL;
		hash->copy_path = path_dirs;
		return ;
	}
	insert_command_value(path_dirs, name_key, command_value);
}
