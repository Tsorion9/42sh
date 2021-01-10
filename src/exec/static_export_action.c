/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_export_action.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 15:05:53 by nriker            #+#    #+#             */
/*   Updated: 2021/01/10 17:07:14 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_export.h"

t_export				*init_t_export(void)
{
	t_export		*export;

	export = ft_memalloc(sizeof(t_export));
	if (export == NULL)
		return (NULL);
	export->hd = init_t_hashdata();
	if (export->hd == NULL)
		return (NULL);
	return (export);
}

t_export				*static_export_action(int action)
{
	static	t_export *export;

	if (action == init)
	{
		if ((export = init_t_export()) == NULL)
			return NULL;
		copy_env_to_exports();
		return (export);
	}
	else if (action == get)
		return (export);
	else if (action == del)
		delete_t_export();
	return (NULL);
}
