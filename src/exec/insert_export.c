/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 16:22:59 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 16:24:34 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void					insert_export(char *key, char *value)
{
	t_export		*export;

	if ((export = static_export_action(get)) == NULL)
		return ;
	insert_hash_value(key, value, export->hd);
}
