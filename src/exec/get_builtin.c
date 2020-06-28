/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:33 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:53 by anton            ###   ########.fr       */
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
	return (NULL);
}
