/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_t_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:14:29 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 15:21:40 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

void					delete_t_export(void)
{
    t_export		*export;

	if ((export = static_export_action(get)) == NULL)
		return ;
    if (export->hd != NULL)
        delete_t_hashdata((&(export->hd)));
    free(export);
}
