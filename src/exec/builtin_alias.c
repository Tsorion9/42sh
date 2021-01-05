/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/05 12:34:05 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "gayprompt.h"
#include "t_hashalias.h"

int			builtin_alias(char **args, t_env env, int subshell)
{
	t_hashalias		*alias;

	if ((alias = static_hashalias_action(get)) == NULL)
		return (EXIT_FAILURE);
	(void)env;
	(void)subshell;
	// (void)args;
	
  	// hash_api_insert_hash_value("cat", "!!!", alias->hd);
 	// hash_api_insert_hash_value("abc", "123", alias->hd);
 	// hash_api_insert_hash_value("cba", "321", alias->hd);

	 
	if (*args == NULL)
		alias_api_print_all_aliases(alias);
	else if (*args && args[1] == NULL)
		alias_api_print_alias(*args);
	else if (*args && !ft_strcmp(args[1], "="))
		alias_api_insert_alias(alias, *args, args[2]);
	// alias->hd = hash_api_init_hash_data();

	// t_hashdata *hd = hash_api_init_hash_data();

 	// hash_api_insert_hash_value("cat", "'      '", alias->hd);
	// hash_api_insert_hash_value("key", "123", alias->hd);
	// alias_api_print_all_aliases(alias);
	return (0);
}
