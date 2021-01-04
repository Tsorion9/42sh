/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/05 00:43:23 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "gayprompt.h"
#include "t_hashalias.h"

int			builtin_alias(char **args, t_env env, int subshell)
{
	t_hashalias		*alias;

	if ((alias = alias_api_init_hash_alias()) == NULL)
		return (EXIT_FAILURE);
	(void)env;
	(void)subshell;
	(void)args;
	if (*args == NULL)
		alias_api_print_all_aliases(alias);
	
	// alias->hd = hash_api_init_hash_data();

	// t_hashdata *hd = hash_api_init_hash_data();

  	// hash_api_insert_hash_value("cat", "!!!", alias->hd);
 	// hash_api_insert_hash_value("abc", "123", alias->hd);
 	// hash_api_insert_hash_value("cba", "321", alias->hd);
 	// // hash_api_insert_hash_value("cat", "'      '", hd);

  	// // hash_api_print_hash_table(hd);
	
	// // t_hashdata *data = hash_api_init_hash_data();
	// hash_api_insert_hash_value("key", "123", alias->hd);

	// alias_api_print_all_aliases(alias);
	
	// hash_api_print_hash_table(alias->hd);
	return (0);
}
