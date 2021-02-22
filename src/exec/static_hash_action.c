/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_hash_action.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 06:45:56 by nriker            #+#    #+#             */
/*   Updated: 2021/02/22 18:19:32 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

t_hash			*static_hash_action(int action)
{
	static t_hash	*hash;
	// char			*env_path;

	if (action == init)
	{
		if ((hash = init_t_hash()) == NULL)
			return NULL;
		// env_path = ft_getenv(env, "PATH");
		hash->copy_path = ft_strsplit(ft_getenv(env, "PATH"), ':');
		return (hash);
	}
	else if (action == get)
		return hash;
	else if (action == del)
	{
		delete_t_hash();
		hash = NULL;
	}
	return (NULL);
}
