/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 07:21:37 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 07:24:45 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			delete_path(void)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return ;
	if (hash->copy_path != NULL)
	{
		del_array(hash->copy_path);
		hash->copy_path = NULL;
	}
}
