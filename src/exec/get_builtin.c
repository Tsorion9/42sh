/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:33 by anton             #+#    #+#             */
/*   Updated: 2021/01/05 12:48:17 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_builtin.h"

t_builtin	get_builtin(char *name)
{
	if (!name)
		return (NULL);
	if (!ft_strcmp(name, "echo"))
		return (&builtin_echo);
	if (!ft_strcmp(name, "cd"))
		return (&builtin_cd);
	if (!ft_strcmp(name, "env"))
		return (&builtin_env);
	if (!ft_strcmp(name, "setenv"))
		return (&builtin_setenv);
	if (!ft_strcmp(name, "getenv"))
		return (&builtin_getenv);
	if (!ft_strcmp(name, "unsetenv"))
		return (&builtin_unsetenv);
	if (!ft_strcmp(name, "exit"))
		return (&builtin_exit);
	if (!ft_strcmp(name, "21shopt"))
		return (&builtin_21shopt);
	if (!ft_strcmp(name, "alias"))
		return (&builtin_alias);
	if (!ft_strcmp(name, "unalias"))
		return (&builtin_unalias);
	return (NULL);
}
