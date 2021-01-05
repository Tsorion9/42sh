/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias_api_print_all_aliases.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:53:42 by nriker            #+#    #+#             */
/*   Updated: 2021/01/05 12:13:08 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hashalias.h"

void		alias_api_print_alias(char *key)
{
	char	*alias;

	alias = alias_api_get_alias(key);
	if (alias)
	{
		ft_putstr(alias);
		ft_putchar('\n');
		free(alias);
	}
}

void		alias_api_print_all_aliases(t_hashalias *hash_alias)
{
	print_table(hash_alias->hd);
}
