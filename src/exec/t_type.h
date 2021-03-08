/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_type.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:22:56 by nriker            #+#    #+#             */
/*   Updated: 2021/03/08 08:10:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_TYPE_H
# define T_TYPE_H

# include "t_hashalias.h"
# include "readline.h"
# include "find_path.h"
# include "t_hash.h"

void			invalid_type_option(char *arg);
void			invalid_type_name(char *copy);
int				check_input(char *args, t_env env);
int				check_in_alias(char *args);
int				check_in_builtins(char *args);
int				check_in_path(char *args);
int				check_in_hash(char *args);

#endif
