/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_invalid_alias.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 17:37:46 by nriker            #+#    #+#             */
/*   Updated: 2021/02/13 16:54:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

void	invalid_alias_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: alias: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "alias: usage: alias [-p] [name[=value] ... ]\n");
}

void	invalid_alias_name(char *copy)
{
	ft_fprintf(STDERR_FILENO, "alias: '%s': invalid alias name\n", copy);
}
