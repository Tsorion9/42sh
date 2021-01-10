/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 23:20:30 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 23:22:35 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

char					*search_export(char *key)
{
	t_export		*export;

	if ((export = static_export_action(get)) == NULL)
		return (NULL);
	return (search_hash_data(key, export->hd));
}
