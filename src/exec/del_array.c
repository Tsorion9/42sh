/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:16 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Free NULL-terminated array of strings
*/

void	*del_array(char **env)
{
	char	**start;

	if (!*env)
	{
		free(env);
		return (NULL);
	}
	start = env;
	while (*env)
		free(*env++);
	free(start);
	return (NULL);
}
