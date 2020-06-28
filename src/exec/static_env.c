/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:43 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:54 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"

t_env	static_env_action(t_env_action action, void *opt_arg)
{
	static t_env	original;
	static t_env	copy;

	if (action == get)
		return (original);
	else if (action == init)
		original = init_env((char **)opt_arg);
	else if (action == save)
		copy = copy_env(original);
	else if (action == restore)
	{
		delenv(original);
		original = copy;
		copy = NULL;
	}
	else
		delenv(original);
	return (NULL);
}
