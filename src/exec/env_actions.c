/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:19 by anton             #+#    #+#             */
/*   Updated: 2021/03/01 21:40:09 by nriker           ###   ########.fr       */
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

int				arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		i++;
	}
	return (i);
}

static int		is_greater_1(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b));
}

/*
** memory_ok - can be null
** optional_prefix - can be null
*/

void			print_env(t_env env, int *memory_ok, char *optional_prefix)
{
	char	**arr;
	char	**start;

	(void)memory_ok;
	arr = to_array(env, memory_ok);
	qsort_void_ptr((void **)arr, arr_len(arr), is_greater_1);
	start = arr;
	while (*arr)
	{
		ft_printf("%s%s\n", optional_prefix ? optional_prefix : "", *arr);
		arr++;
	}
	del_array(start);
}
