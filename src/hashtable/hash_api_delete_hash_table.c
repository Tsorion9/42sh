/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_api_delete_hash_table.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 18:02:53 by nriker            #+#    #+#             */
/*   Updated: 2021/01/04 18:07:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "hashtable.h"

int					hash_api_delete_hash_table(char *key, t_hashtable **table)
{
	t_hashtable		*table_prev;

	table_prev = NULL;
	(void)table;
	(void)key;
	// while (table)
	// {
		
	// }
	if (!table)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
