/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 17:10:55 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/01 22:01:22 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, void *src, size_t len)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			i;

	if (dst == NULL && src == NULL)
		return (NULL);
	ptr1 = (unsigned char*)dst;
	ptr2 = (unsigned char*)src;
	i = 0;
	if (ptr2 < ptr1)
		while ((int)(--len) >= 0)
			ptr1[len] = ptr2[len];
	else
		while (i < len)
		{
			ptr1[i] = ptr2[i];
			i++;
		}
	return (dst);
}
