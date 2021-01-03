/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hashalias.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:40:12 by nriker            #+#    #+#             */
/*   Updated: 2021/01/03 14:12:08 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef T_HASHALIAS_H
# define T_HASHALIAS_H

# include "environment.h"
# include "hashtable.h"

/*
** Hashtable for builtins Alias/Unalias
*/

typedef struct			s_hashalias
{
	t_hashdata			*hd;
	int					table_size;
}						t_hashalias;


/*
** API for t_hashalias
** static_hashalias_action - to init/get/free t_hashalias
** insert_alias - insert value with key into hash-table
** delete_hashalias - delete hash-table
*/

t_hashalias				*static_hashalias_action(int action);
void					*alias_api_insert_alias(char *key, char *value);
void					alias_api_delete_hashalias(t_hashalias *hash_alias);

/*
** API FOR JSANCE
** get_alias - get value of alias or NULL if alias is't exist
*/

char					*alias_api_get_alias(char *key);

#endif
