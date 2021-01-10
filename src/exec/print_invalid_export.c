/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_invalid_export.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 18:08:50 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 18:09:58 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void	invalid_export_option(char *arg)
{
	ft_fprintf(2, "42sh: export: %s: invalid option\n", arg);
	ft_fprintf(2, "export: usage: export [-pn] [name[=value] ... ]\n");
}

void	invalid_export_name(char *copy)
{
	ft_fprintf(2, "export: '%s': invalid export name\n", copy);
}
