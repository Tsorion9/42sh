/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_del.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:48:44 by bgian             #+#    #+#             */
/*   Updated: 2019/10/09 20:33:34 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Content size is neeeded only for libft compatability
*/

void	del_simple(void *content, size_t content_size)
{
	if (content_size > 0)
		free(content);
}
