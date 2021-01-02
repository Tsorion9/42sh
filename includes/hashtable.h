/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtable.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 18:48:59 by nriker            #+#    #+#             */
/*   Updated: 2021/01/02 22:34:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTABLE_H
# define HASHTABLE_H

/*
** API for Hash-table
** hash_function - get index in hash-table by key
** insert_hash_value - insert value into hash table. Return hash-table with new value
** get_hash_value - get value from hash-table by key. Return value from hash-table
** delete_hash_table - delete hash-table
*/

int						hash_api_hash_function(char *key);
char					**hash_api_insert_hash_value(char *key, char *value);
char					*hash_api_get_hash_value(char *key, char **table);
void					hash_api_delete_hash_table(char **table);

#endif
