/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 19:28:14 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/12 19:29:30 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	pos;
	size_t	nlen;

	i = 0;
	nlen = ft_strlen(needle);
	if (haystack == needle)
		return ((char*)haystack);
	if (nlen == 0)
		return ((char*)haystack);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i < len)
	{
		pos = 0;
		while (haystack[i + pos] == needle[pos] && haystack[i + pos] != '\0')
		{
			if ((pos == nlen - 1) && (i + pos) <= len)
				return ((char*)haystack + i);
			pos++;
		}
		i++;
	}
	return (NULL);
}
