/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:36 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"

/*
** Split s to key and value
** s = "V1=val1", then key = "V1", value = "val1"
** If no '=' is in s, do not do anything; Return 2
** return 0 in case of memory errors
** else return 1;
*/

int				split_env_entry(char *s, char **key, char **value)
{
	char	*v;

	if (!(v = ft_strchr(s, '=')))
		return (2);
	if (!(v = ft_strchr(s, '=') + 1))
		return (2);
	if (!(*value = ft_strnew(ft_strlen(v))))
		return (0);
	if (!(*key = ft_strnew(v - s)))
	{
		free(*value);
		*value = 0;
		return (0);
	}
	ft_strncpy(*key, s, v - s - 1);
	ft_strncpy(*value, v, ft_strlen(v));
	return (1);
}

t_env			init_env(char **environ)
{
	t_ptree	*tree;
	char	*key;
	char	*value;
	int		status;

	if (!(tree = new_tree()))
		return (NULL);
	while (*environ)
	{
		if (!(status = split_env_entry(*environ, &key, &value)))
		{
			del_tree(&tree);
			return (NULL);
		}
		if (status == 1 && !insert_value(tree, key, value))
			return (NULL);
		free(key);
		key = 0;
		value = 0;
		environ++;
	}
	return ((t_env)tree);
}
