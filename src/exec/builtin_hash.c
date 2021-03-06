/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:41:13 by nriker            #+#    #+#             */
/*   Updated: 2021/03/01 23:14:20 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"
#include "find_path.h"
#include "t_type.h"

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
	int		builtin;
	char	*str;

	i = 0;
	builtin = 0;
	while (args[i])
	{
		if ((str = search_hash(args[i])) == NULL)
		{
			if ((str = find_path(args[i])) && (builtin = check_in_builtins(args[i])))
				insert_hash(args[i], str);
			else if (builtin)
				ft_fprintf(2, "42sh: hash: %s: not found\n", args[i]);
		}
		else
			delete_hash(args[i]);
		free(str);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		builtin_hash(char **args, t_env envs, int subshell)
{
	(void)envs;
	(void)subshell;
	if (!*args && is_hash_empty() == EXIT_SUCCESS)
	{
		ft_printf("hash: hash table empty\n");
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
