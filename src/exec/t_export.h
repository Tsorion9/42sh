/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:58:58 by nriker            #+#    #+#             */
/*   Updated: 2021/01/11 20:39:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_EXPORT_H
# define T_EXPORT_H

# include "t_hashalias.h"

/*
** Hashtable for builtin Export
*/

typedef struct			s_export
{
	t_hashdata			*hd;
	int					size;
	int					flag_n;
}						t_export;

void					copy_env_to_exports(void);
int						delete_export(char *key);
void					delete_t_export(void);
void					insert_export(char *key, char *value);
char					*search_export(char *key);
void					print_export(char *key);
void					print_exports(void);
char					**export_to_array(void);
int						check_flag_pn(char ***args, void (*print)(void),
							void (*invalid_print)(char *arg));
void					invalid_export_option(char *arg);
void					invalid_export_name(char *copy);

# endif
