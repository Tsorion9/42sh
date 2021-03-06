/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hashalias.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:40:12 by nriker            #+#    #+#             */
/*   Updated: 2021/02/28 16:10:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HASHALIAS_H
# define T_HASHALIAS_H

# include "environment.h"
# include "hashtable.h"

typedef enum	e_alias_action
{
	init,
	get,
	del
}				t_alias_action;

/*
** Hashtable for builtins Alias/Unalias
*/

typedef struct			s_hashalias
{
	t_hashdata			*hd;
}						t_hashalias;

/*
** API for BUILTIN ALIAS
** get_alias_args - allow get mas of args for builtin alias
** static_hashalias_action - to init/get/del t_hashalias
** insert_alias - insert value with key into hash-table
** delete_hashalias - delete hash-table
*/

t_hashalias				*static_hashalias_action(int action);
t_hashalias				*init_t_hashalias(void);
char					**get_alias_args(char **args,
							void (*invalid_print)(char *arg));
void					delete_t_hashalias(void);
void					insert_alias(char *key, char *value);
void					print_alias(char *key);
void					print_all_aliases(void);
void					invalid_alias_name(char *copy);
void					invalid_alias_option(char *arg);
int						check_flag_p(char ***args, void (*print)(void),
							void (*invalid_print)(char *arg));
int						check_valid_symbol(char *key, char *copy, int i,
							void (*print)(char *copy));
int						check_valid_flag(char *arg, void (*print)(char *arg));
void					set_null_meet_alias(void);

/*
** API FOR ALIAS
** search_alias - get value (don't forget to free string)
** of alias or NULL if alias is't exist
*/

char					*search_alias(char *key);
t_hashtable				*search_alias_hash_element(char *key);
t_hashtable				*check_tokbuf(char *key, char *value);
t_hashtable				*get_hashtable_by_key(char *key, char *value);
void					set_do_not_expand(t_token **token);
void					delete_first_token(t_deque **tokbuf_g);
void					value_of_token_is_not_null(t_token *token,
							t_deque **tokbuf_g, int *not_empty_links);
void					non_string_alias(t_token *token,
										 t_deque **tokbuf_fresh);
void					flush_tokbuf_back(t_deque **destination, t_deque *src);

// void		upgrade_tokbuf(char *key, char *value);

/*
** API for BUILTIN UNALIAS
*/

int						delete_alias(char *key);

#endif
