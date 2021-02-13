/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_invalid_type.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 08:22:05 by nriker            #+#    #+#             */
/*   Updated: 2021/02/13 16:54:27 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_type.h"

void	invalid_type_option(char *arg)
{
	ft_fprintf(STDERR_FILENO, "42sh: type: %s: invalid option\n", arg);
	ft_fprintf(STDERR_FILENO, "type: usage: type name [name ...]\n");
}

void	invalid_type_name(char *copy)
{
	ft_fprintf(STDERR_FILENO, "42sh: type: %s: not found\n", copy);
}
