/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_builtin.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 02:02:56 by anton             #+#    #+#             */
/*   Updated: 2021/01/07 11:44:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef T_BUILTIN_H
# define T_BUILTIN_H

# include "environment.h"

typedef	int	(*t_builtin)(char **args, t_env env, int subhell);

int			builtin_echo(char **args, t_env env, int subshell);
int			builtin_cd(char **args, t_env env, int subshell);
int			builtin_getenv(char **args, t_env env, int subshell);
int			builtin_setenv(char **args, t_env env, int subshell);
int			builtin_unsetenv(char **args, t_env env, int subshell);
int			builtin_env(char **args, t_env env, int subshell);
int			builtin_exit(char **args, t_env env, int subshell);
int			builtin_21shopt(char **args, t_env env, int subshell);
int			builtin_alias(char **args, t_env env, int subshell);
int			builtin_unalias(char **args, t_env env, int subshell);
int			builtin_jobs(char **args, t_env env, int subshell);
int			builtin_bg(char **args, t_env env, int subshell);
int			builtin_fg(char **args, t_env env, int subshell);
int			builtin_export(char **args, t_env env, int subshell);
int			builtin_fc(char **args, int subshell);

t_builtin	get_builtin(char *name);

#endif
