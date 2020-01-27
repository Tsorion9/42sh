/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:32:48 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/10 22:19:54 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size_strtrim(const char *s)
{
	int		size;
	int		i;

	size = 0;
	i = ft_strlen(s) - 1;
	while ((s[i] == ' ' || s[i] == '\n' || s[i] == '\t') && i != -1)
	{
		size++;
		i--;
	}
	if (i == -1)
		return (0);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
	{
		size++;
		i++;
	}
	return (ft_strlen(s) - size);
}

char		*ft_strtrim(const char *s)
{
	char	*res;
	int		i;
	int		size;
	int		j;

	if (s == NULL)
		return (NULL);
	size = ft_size_strtrim(s);
	if (!(res = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	j = 0;
	while (j < size)
	{
		res[j] = s[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}
