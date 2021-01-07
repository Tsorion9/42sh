/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/07 15:32:44 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void		get_key_and_value(char ***mas_args, char *args, int *i)
{
	(*mas_args)[(*i)] = ft_strcut(args, '=');
	(*mas_args)[(*i) + 1] = ft_strdup("=");
	(*mas_args)[(*i) + 2] = ft_strcut(ft_strchr(args, '=') + 1, '\0');
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
		else if (ft_strlen(ft_strchr(*args, '=')) != ft_strlen(*args))
			if (*(ft_strchr(*args, '=') - 1) != '='
				&& *(ft_strchr(*args, '=') + 1) != '=')
				size += 3;
		args++;
	}
	return (size);
}

char		**get_mas_args(char **args)
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

void		builtin_alias_cycle_args(char **mas_args)
{
	int		i;

	i = 0;
	while (mas_args[i])
	{
		if (mas_args[i] && (mas_args[i + 1] == NULL
			|| ft_strcmp(mas_args[i + 1], "=")))
			print_alias(mas_args[i++]);
		else if (mas_args[i] && !ft_strcmp(mas_args[i + 1], "="))
		{
			insert_alias(mas_args[i], mas_args[i + 2]);
			i += 3;
		}
	}
}

int			builtin_alias(char **args, t_env env, int subshell)
{
	char	**mas_args;

	mas_args = NULL;
	(void)env;
	(void)subshell;
	if (*args == NULL)
		print_all_aliases();
	else
	{
		if ((mas_args = get_mas_args(args)) != NULL)
			builtin_alias_cycle_args(mas_args);
		if (mas_args != NULL)
			del_array(mas_args);
	}
	return (EXIT_FAILURE);
}
