/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 23:11:42 by nriker            #+#    #+#             */
/*   Updated: 2021/01/11 20:39:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

int			delete_export(char *key)
{
	t_export		*export;

	if ((export = static_export_action(get)) == NULL)
		return (EXIT_FAILURE);
	if ((delete_t_hashtable(key, &(export->hd))) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	export->size--;
	return (EXIT_SUCCESS);
}
