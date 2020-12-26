/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 20:11:48 by nriker            #+#    #+#             */
/*   Updated: 2020/12/26 20:13:19 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

char	*ft_strcut(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !ft_strchr(s, c))
		return (NULL);
	while (s[i] != (char)c)
		i++;
	if ((str = ft_strnew(i + 1)))
		return (ft_strncpy(str, s, i));
	return (NULL);
}
