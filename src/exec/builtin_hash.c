/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:41:13 by nriker            #+#    #+#             */
/*   Updated: 2021/02/13 12:27:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"

int		check_hash_params(char **args)
{
	int		i;

	i = 0;
	while (args[i])
	{
		if (search_hash(args[i]) == NULL)
		{
			ft_printf("42sh: hash: %s: not found", args[i]);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int		builtin_hash(char **args, t_env env, int subshell)
{
	t_hash			*hash;
	t_hashtable		*table;
	t_hashtable		*table_copy;

	(void)env;
	(void)subshell;
	if (((hash = static_hash_action(get)) == NULL) ||
		is_hash_empty() == EXIT_SUCCESS)
		ft_printf("hash: hash table empty\n");
	if (!*args)
	{
		ft_printf("hits\t\tcommand");
		// print_all_hash();
		return (EXIT_SUCCESS);
	}
	if (!ft_strcmp(args[0], "-r"))
	{
		static_hash_action(del);
		static_hash_action(init);
	}	
	return (check_hash_params(args));
}