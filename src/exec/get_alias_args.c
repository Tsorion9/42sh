/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_alias_args.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:41:48 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:29:40 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

int			create_key(char *key, void (*invalid_print)(char *arg))
{
	int		i;
	char	*copy;

	i = 0;
	if (ft_strchr(key, '/') != NULL)
	{
		invalid_print(key);
		return (EXIT_FAILURE);
	}
	if ((copy = ft_strdup(key)) == NULL)
		return (EXIT_FAILURE);
	while (key[i])
	{
		if (check_valid_symbol(key, copy, i, invalid_alias_option) == EXIT_FAILURE)
		{
			free(copy);
			return (EXIT_FAILURE);
		}
		else
			i++;
	}
	free(copy);
	return (EXIT_SUCCESS);
}

void		create_value(char *key)
{
	int		i;

	i = 0;
	while (key[i])
	{
		if (key[i] == '\'' || key[i] == '"' ||
			(key[i] == '\\' && key[i + 1] == '\0'))
			delete_symbol_in_str(key, i);
		else
			i++;
	}
}

int			get_key_and_value(char ***mas_args, char *args, int *i,
				void (*invalid_print)(char *arg))
{
	(*mas_args)[(*i)] = ft_strcut(args, '=');
	(*mas_args)[(*i) + 1] = ft_strdup("=");
	if (*(ft_strchr(args, '=') + 1) != '\0')
		(*mas_args)[(*i) + 2] = ft_strcut(ft_strchr(args, '=') + 1, '\0');
	else
		(*mas_args)[(*i) + 2] = ft_strdup("''");
	if (create_key((*mas_args)[(*i)], invalid_print) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	create_value((*mas_args)[(*i) + 2]);
	(*i) += 3;
	return (EXIT_SUCCESS);
}

int			get_size_of_mas_args(char **args)
{
	int		size;

	size = 0;
	while (*args)
	{
		if (ft_strchr(*args, '=') == NULL)
			size++;
		else if (ft_strlen(ft_strchr(*args, '=')) != ft_strlen(*args))
			size += 3;
		args++;
	}
	return (size);
}

char		**get_alias_args(char **args, void (*invalid_print)(char *arg))
{
	char	**mas_args;
	int		i;

	i = 0;
	if (get_size_of_mas_args(args) == 0 || (mas_args = (char**)ft_memalloc(\
		sizeof(char*) * (get_size_of_mas_args(args) + 1))) == NULL)
		return (NULL);
	while (*args)
	{
		if (ft_strchr(*args, '=') == NULL)
		{
			if ((mas_args[i] = ft_strdup(*args)) == NULL)
				return (NULL);
			i++;
		}
		else if (ft_strlen(ft_strchr(*args, '=')) != ft_strlen(*args)
			&& (get_key_and_value(&mas_args, *args, &i, invalid_print) == EXIT_FAILURE))
		{
			if (mas_args)
				del_array(mas_args);
			return (NULL);
		}
		args++;
	}
	return (mas_args);
}
