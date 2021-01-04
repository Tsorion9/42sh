/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:40 by mphobos           #+#    #+#             */
/*   Updated: 2021/01/04 20:10:41 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "readline.h"

char	*get_prompt(int which)
{
	char	*res;

	if (which == PS1)
		res = ft_getenv(env, "PS1");
	else
		res = ft_getenv(env, "PS2");
	if (!res)
		return ("");
	return (res);
}
