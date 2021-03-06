/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_t_hash.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 06:54:32 by nriker            #+#    #+#             */
/*   Updated: 2021/02/10 06:56:58 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hash.h"

void			delete_t_hash(void)
{
	t_hash		*hash;

	if ((hash = static_hash_action(get)) == NULL)
		return ;
	if (hash->hd != NULL)
	    delete_t_hashdata((&(hash->hd)));
	if (hash->copy_path != NULL)
		del_array(hash->copy_path);
	free(hash);
}
