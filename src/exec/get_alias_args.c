/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alias_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:41:48 by nriker            #+#    #+#             */
/*   Updated: 2021/01/08 15:00:18 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		get_key_and_value(char ***mas_args, char *args, int *i)
{
	(*mas_args)[(*i)] = ft_strcut(args, '=');
	(*mas_args)[(*i) + 1] = ft_strdup("=");
	if (*(ft_strchr(args, '=') + 1) != NULL)
		(*mas_args)[(*i) + 2] = ft_strcut(ft_strchr(args, '=') + 1, '\0');
	else
		(*mas_args)[(*i) + 2] = ft_strdup("''");
	(*i) += 3;
}

int			get_size_of_mas_args(char **args)
{
	int		size;

	size = 0;
	while (*args)
	{
		if (ft_strchr(*args, '=') == NULL)
			size++;
		else if (ft_strlen(ft_strchr(*args, '=')) != ft_strlen(*args)
			&& *(ft_strchr(*args, '=') - 1) != '='
			&& *(ft_strchr(*args, '=') + 1) != '=')
				size += 3;
		args++;
	}
	return (size);
}

char		**get_alias_args(char **args)
{
	char	**mas_args;
	int		i;

	i = 0;
	if (get_size_of_mas_args(args) == 0)
		return (NULL);
	mas_args = (char**)ft_memalloc(sizeof(char*) *
		(get_size_of_mas_args(args) + 1));
	while (*args)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			if ((mas_args[i] = ft_strdup(*args)) == NULL)
				return (NULL);
			i++;
		}
		else if (ft_strlen(ft_strchr(*args, '=')) != ft_strlen(*args)
			&& *(ft_strchr(*args, '=') - 1) != '='
			&& *(ft_strchr(*args, '=') + 1) != '=')
			get_key_and_value(&mas_args, *args, &i);
		args++;
	}
	return (mas_args);
}
