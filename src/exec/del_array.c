/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:16 by anton             #+#    #+#             */
/*   Updated: 2020/12/16 20:48:36 by jsance           ###   ########.fr       */
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
