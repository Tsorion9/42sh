/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:25 by anton             #+#    #+#             */
/*   Updated: 2021/01/08 13:40:09 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "inc21sh.h"

/*
** TODO: exit status must be static
*/

int	builtin_exit(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	(void)args; // TODO: arg1 is exit status
	reset_exit(0); // Do not need to reset sometimes?
	return (0);
}
