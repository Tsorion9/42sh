/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:48:59 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 11:20:34 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "inc21sh.h"
# include "deque.h"

/*
** HASH_SIZE - base size for hash_table. Using in hash_function
*/

# define HASH_SIZE 100

typedef struct			s_hashtable
{
	char				*key;
	char				*value;
	t_deque				*tokbuf_value;
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
** delete_t_hashdate - delete all hash-table
** delete_t_hashtable - delete element from hash-table
** print_hash_table - print all elements from hash-table
*/

unsigned int			hash_function(char *key);
t_hashdata				*init_t_hashdata(void);
int						insert_hash_value(char *key, char *value,
							t_hashdata *hd);
char					*search_hash_data(char *key, t_hashdata *hd);
void					delete_t_hashdata(t_hashdata **hd);
int						delete_t_hashtable(char *key, t_hashdata **hd);
void					delete_hash_table_element(t_hashtable **table);
void					print_table(t_hashdata *hd);
void					print_hash_table(t_hashdata *hd);
t_deque					*search_queue(char *key, t_hashdata *hd);
t_deque					*search_tokbuf(char *key);

#endif
