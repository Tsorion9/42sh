/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_misc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:42:20 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 13:42:21 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void			del_list(void *mem, size_t garbage)
{
	(void)garbage;
	free(mem);
}

int				is_greater(void *a, void *b)
{
	return (ft_strcmp((char *)a, (char *)b));
}
