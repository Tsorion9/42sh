/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:58:58 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:11:30 by nriker           ###   ########.fr       */
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
}						t_export;

t_export				*static_export_action(int action);
void					copy_env_to_exports(void);
void					delete_t_export(void);
void					insert_export(char *key, char *value);
char					*search_export(char *key);
void					print_export(void);
void					print_exports(void);
char					**exports_to_array(void);
void					invalid_export_option(char *arg);
void					invalid_export_name(char *copy);

# endif
