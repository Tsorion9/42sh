/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_all_aliases.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 23:53:42 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 10:04:59 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "t_hashalias.h"

void		print_alias(char *key)
{
	char	*alias;

	alias = search_alias(key);
	if (alias)
	{
		ft_printf("%s=%s\n", key, alias);
		free(alias);
	}
}

void		print_all_aliases(void)
{
	t_hashalias		*hash_alias;

	if ((hash_alias = static_hashalias_action(get)) == NULL)
		return ;
	print_table(hash_alias->hd);
}
