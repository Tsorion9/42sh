/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 11:34:50 by anton             #+#    #+#             */
/*   Updated: 2021/01/02 21:44:58 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "environment.h"
#include "gayprompt.h"
#include "t_hashalias.h"

// static int	print_usage(void)
// {
// 	ft_putstr_fd("Usage: 21shopt option_name new_value\n", 2);
// 	return (0);
// }

int			builtin_alias(char **args, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	(void)args;
	ft_putstr("alias\n");
	// if (!*args)
	// 	return (print_usage());
	// if (!ft_strcmp(*args, "gaymode"))
	// {
	// 	args++;
	// 	if (!*args)
	// 	{
	// 		ft_fprintf(2, "%s", "Please, select mode (on/off)\n");
	// 		return (0);
	// 	}
	// 	if (!ft_strcmp(*args, "on"))
	// 		return (update_gaymode(1, 1));
	// 	if (!ft_strcmp(*args, "off"))
	// 		return (update_gaymode(1, 0));
	// 	ft_fprintf(2, "Unknown mode: %s (valid options: on, off)\n", *args);
	// }
	// ft_fprintf(2, "Unknown option: %s\n", *args);
	// ft_fprintf(2, "Valid option: %s\n", "gaymode");
	return (0);
}
