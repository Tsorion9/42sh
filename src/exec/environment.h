/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:55 by anton             #+#    #+#             */
/*   Updated: 2020/12/26 18:36:48 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H

# include <unistd.h>
# include "libft.h"

typedef t_ptree *t_env;

/*
** ENVIROMENT API for getting info from env
** Convert between tree and char ** representations.
*/

int				split_env_entry(char *s, char **key, char **value);
t_env			init_env(char **environ);
char			**to_array(t_env env, int *memory_ok);

void			*del_array(char **arr);
void			delenv(t_env env);

char			**env_api_get_mas_vars(char **arr);

char			*ft_getenv(t_env env, char *name);
t_env			copy_env(t_env env);
int				ft_setenv(t_env env, char *name, char *value);
void			ft_unsetenv(t_env env, char *name);
void			print_env(t_env env, int *memory_ok);


#endif
