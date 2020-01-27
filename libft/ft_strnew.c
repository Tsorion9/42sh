/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 16:13:24 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/10 16:14:33 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*res;

	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	if (size != 0)
	{
		res[size] = '\0';
		ft_memset(res, 0, size);
	}
	return (res);
}
