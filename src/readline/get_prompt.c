/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:40 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:12:48 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "static_env.h"
#include "inc21sh.h"

char	*get_prompt(int which)
{
	char	*res;

	if (which == PS1)
		res = ft_getenv(static_env_action(get, NULL), "PS1");
	else
		res = ft_getenv(static_env_action(get, NULL), "PS2");
	if (!res)
		return ("");
	return (res);
}
