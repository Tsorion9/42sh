/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:48:59 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 00:38:28 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "inc21sh.h"

/*
** HASH_SIZE - base size for hash_table. Using in hash_function
*/

# define HASH_SIZE 100

typedef struct			s_hashtable
{
	char				*key;
	char				*value;
	struct s_hashtable	*next;
}						t_hashtable;

typedef struct			s_hashdata
{
	t_hashtable			*hashtable[HASH_SIZE];
	int					if_has_content;
}						t_hashdata;

/*
** API for Hash-table
** hash_function - get index in hash-table by key
** insert_hash_value - insert value into hash table.
** Return hash-table with new value
** get_hash_value - get value from hash-table by key.
** Return value from hash-table
** delete_hash_date - delete all hash-table
** delete_hash_table - delete element from hash-table
** print_hash_table - print all elements from hash-table
*/

int						hash_api_hash_function(char *key);
t_hashdata				*hash_api_init_hash_data(void);
int						hash_api_insert_hash_value(char *key, char *value,
							t_hashdata *hd);
char					*hash_api_get_hash_data(char *key, t_hashdata *hd);
void					hash_api_delete_hash_date(t_hashdata **hd);
int						hash_api_delete_hash_table(char *key, t_hashdata **hd);
void					delete_hash_table_element(t_hashtable **table);
void					print_table(t_hashdata *hd);
void					hash_api_print_hash_table(t_hashdata *hd);

#endif
