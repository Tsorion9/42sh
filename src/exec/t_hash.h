/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_hash.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 00:01:25 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 08:51:33 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_HASH_H
# define T_HASH_H

# include "environment.h"
# include "hashtable.h"

typedef enum	e_hash_action
{
	init,
	get,
	del
}				t_hash_action;

typedef struct			s_hash
{
	t_hashdata			*hd;
	char				**copy_path;
}						t_hash;

t_hash			*static_hash_action(int action);
t_hash			*init_t_hash(void);
void			delete_t_hash(void);
void			insert_hash(char *key, char *value);
void			insert_hash_path(char **path);
void			print_hash(char *key);
void			print_all_aliases(void);
char			*search_hash(char *key);
int				delete_hash(char *key);
void			delete_path(void);
int				is_hash_empty(void);
int				is_path_was_changed(char **copy_path, char **path);

#endif
