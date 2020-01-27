/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_srtlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 21:20:28 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/08 22:55:39 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;
	size_t	start_len;

	len = ft_strlen(dst);
	start_len = len;
	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && len < size - 1)
	{
		dst[len] = src[i];
		len++;
		i++;
	}
	if (size < start_len)
		return (size + ft_strlen(src));
	dst[len] = '\0';
	return (start_len + ft_strlen(src));
}
