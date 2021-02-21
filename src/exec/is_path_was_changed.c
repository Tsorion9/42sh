/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_path_was_changed.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:43:49 by nriker            #+#    #+#             */
/*   Updated: 2021/02/18 22:30:59 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

int				compare_arrays(char **copy_path, char **path)
{
	int		i;
	int		k;

	i = 0;
	if (copy_path == NULL || path == NULL)
		return (EXIT_SUCCESS);
	while (copy_path[i] && path[i])
	{
		if (ft_strcmp(*copy_path, *path))
			return (EXIT_SUCCESS);
	}
	if ((!copy_path[i] && path[i]) || (copy_path[i] && !path[i]))
		return (EXIT_SUCCESS);
	return (EXIT_FAILURE);
}

int				is_path_was_changed(char **copy_path, char **path)
{
	if ((path == NULL && copy_path) || (path && copy_path == NULL))
		return (EXIT_SUCCESS);
	return (compare_arrays(copy_path, path));
}
