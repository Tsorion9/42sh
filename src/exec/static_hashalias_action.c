/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_hashalias_action.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:10:17 by nriker            #+#    #+#             */
/*   Updated: 2021/01/07 10:32:03 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_hashalias.h"

t_hashalias				*static_hashalias_action(int action)
{
	static t_hashalias	*alias;

	if (action == init)
	{
		if ((alias = init_t_hashalias()) == NULL)
			return NULL;
		return alias;
	}
	else if (action == get)
		return alias;
	else if (action == del)
		delete_t_hashalias();
	return (NULL);
}
