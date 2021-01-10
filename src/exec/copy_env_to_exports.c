/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_env_to_exports.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:04:51 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:27:46 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void		insert_cycle(char *key, char *value)
{
		insert_export(key, value);
		if (key)
			free(key);
		if (value)
			free(value);
		key = NULL;
		value = NULL;
}

void		copy_env_to_exports(void)
{
	char	*key;
	char	*value;
	char	**mas_env;
	int		memory_ok;
	int		i;

	key = NULL;
	value = NULL;
	memory_ok = 0;
	i = 0;
	mas_env = to_array(env, &memory_ok);
	if ((mas_env = to_array(env, &memory_ok)) == NULL || !memory_ok)
		return ;
	while (mas_env[i])
	{
		split_env_entry(mas_env[i++], &key, &value);
		insert_cycle(key, value);
	}
	del_array(mas_env);
}
