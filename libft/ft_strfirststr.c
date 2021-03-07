/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfirststr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 14:49:19 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 14:49:20 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_strfirststr(const char *haystack, const char *needle)
{
	size_t	i;

	i = 0;
	while (needle[i] != '\0' && haystack[i] != '\0')
	{
		if (haystack[i] != needle[i])
			return (0);
		i++;
	}
	if (needle[i] != '\0')
		return (0);
	return (1);
}
