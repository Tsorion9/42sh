/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 21:36:10 by nriker            #+#    #+#             */
/*   Updated: 2021/03/01 21:38:47 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"

/*
** Name should be freed later by caller
*/

int				ft_setenv(t_env env, char *name, char *value)
{
	if (!ft_strcmp("PATH", name))
	{
		delete_t_hash();
		static_hash_action(init);
	}
	return (insert_value((t_ptree *)env, name, value));
}

void			ft_unsetenv(t_env env, char *name)
{
	del_key((t_ptree *)env, name);
}
