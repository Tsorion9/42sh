/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_hash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 23:41:13 by nriker            #+#    #+#             */
/*   Updated: 2021/03/14 09:44:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hash.h"
#include "find_path.h"

void	invalid_hash_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: hash: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "hash: usage: hash [-rd] [name ... ]\n");
}

int		check_hash_params(char **args)
{
	int		i;
	char	*str;
	int		status;

	i = 0;
	status = EXIT_SUCCESS;
	while (args[i])
	{
		if ((str = search_hash(args[i])) == NULL)
		{
			if ((str = find_path(args[i])))
				insert_hash(args[i], str);
			else
				ft_fprintf(STDERR_FILENO, "42sh: hash: %s: not found\n",
																	args[i]);
			status = EXIT_FAILURE;
		}
		else
			print_hash(args[i]);
		free(str);
		i++;
	}
	return (status);
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
	if (check_hash_flags(&args, invalid_hash_option) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (check_hash_params(args));
}
