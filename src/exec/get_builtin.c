/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:33 by anton             #+#    #+#             */
/*   Updated: 2021/02/09 07:46:30 by nriker           ###   ########.fr       */
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
	if (!ft_strcmp(name, "set"))
		return (&builtin_set);
	if (!ft_strcmp(name, "unset"))
		return (&builtin_unset);
	if (!ft_strcmp(name, "exit"))
		return (&builtin_exit);
	if (!ft_strcmp(name, "21shopt"))
		return (&builtin_21shopt);
	if (!ft_strcmp(name, "alias"))
		return (&builtin_alias);
	if (!ft_strcmp(name, "unalias"))
		return (&builtin_unalias);
	if (!ft_strcmp(name, "jobs"))
		return (&builtin_jobs);
	if (!ft_strcmp(name, "bg"))
		return (&builtin_bg);
	if (!ft_strcmp(name, "fg"))
		return (&builtin_fg);
	if (!ft_strcmp(name, "export"))
		return (&builtin_export);
	if (!ft_strcmp(name, "fc"))
		return (&builtin_fc);
	if (!ft_strcmp(name, "type"))
		return (&builtin_type);
	return (NULL);
}
