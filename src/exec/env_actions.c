/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:19 by anton             #+#    #+#             */
/*   Updated: 2020/12/16 20:42:00 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

void			delenv(t_env env)
{
	del_tree((t_ptree **)&env);
}

t_env			copy_env(t_env env)
{
	return ((t_env)copy_ptree((t_ptree *)env));
}

/*
** Name should be freed later by caller
*/

int				ft_setenv(t_env env, char *name, char *value)
{
	return (insert_value((t_ptree *)env, name, value));
}

void			ft_unsetenv(t_env env, char *name)
{
	del_key((t_ptree *)env, name);
}

/*
** memory_ok - can be null
** optional_prefix - can be null
*/
void			print_env(t_env env, int *memory_ok, char *optional_prefix)
{
	char	**arr;
	char	**start;

	arr = to_array(env, memory_ok);
	if (!(*memory_ok))
		return ;
	start = arr;
	while (*arr)
	{
		ft_printf("%s%s\n", optional_prefix ? optional_prefix : "" ,*arr);
		arr++;
	}
	del_array(start);
}
