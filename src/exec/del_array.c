/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:16 by anton             #+#    #+#             */
/*   Updated: 2021/01/10 17:17:17 by nriker           ###   ########.fr       */
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
