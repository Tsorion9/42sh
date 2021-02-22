/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:41:13 by nriker            #+#    #+#             */
/*   Updated: 2021/02/22 19:32:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"
#include "find_path.h"

void	invalid_hash_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: hash: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "hash: usage: hash [-r] [name ... ]\n");
}

int			check_valid_flag_hash(char *arg, void (*print)(char *arg))
{
	int		i;

	i = 0;
	if (arg == NULL)
		return (EXIT_SUCCESS);
	while (arg[i] == '\\')
		i++;
	if (arg[i] == '-')
	{
		print(arg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int			check_flag_r(char ***args, void (*invalid_print)(char *arg))
{
	if (**args != NULL && !ft_strcmp(**args, "-r"))
	{
		static_hash_action(del);
		static_hash_action(init);
		(*args)++;
		while (**args != NULL && !ft_strcmp(**args, "-r"))
			(*args)++;
		return (check_valid_flag_hash(**args, invalid_print));
	}
	return (check_valid_flag_hash(**args, invalid_print));
}

int		check_hash_params(char **args)
{
	int		i;
	char	*str;

	i = 0;
	while (args[i])
	{
		if ((str = search_hash(args[i])) == NULL)
		{
			ft_fprintf(STDERR_FILENO, "42sh: hash: %s: not found\n", args[i]);
			return (EXIT_SUCCESS);
		}
		else
			free(str);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		builtin_hash(char **args, t_env envs, int subshell)
{
	t_hash			*hash;
	t_hashtable		*table;
	t_hashtable		*table_copy;

	(void)env;
	(void)subshell;
	if (is_hash_empty() == EXIT_SUCCESS)
	{
		ft_fprintf(STDERR_FILENO, "hash: hash table empty\n");
		return (EXIT_SUCCESS);
	}
	if (!*args && is_hash_empty())
	{
		ft_printf("command\t\tpath\n");
		print_all_hash();
		return (EXIT_SUCCESS);
	}
	if (check_flag_r(&args, invalid_hash_option) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	return (check_hash_params(args));
}