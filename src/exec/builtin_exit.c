/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:25 by anton             #+#    #+#             */
/*   Updated: 2021/01/09 21:45:26 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "inc21sh.h"
#include "libft.h"

/*
** TODO: exit status must be static
*/

int	builtin_exit(char **args, t_env env, int subshell)
{

	(void)env;
	(void)subshell;
	reset_exit(args[0] ? ft_atoi(args[0]) : 0);
	return (0);
}
