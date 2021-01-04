/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfreefree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:53:54 by nriker            #+#    #+#             */
/*   Updated: 2019/10/15 15:58:01 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfreefree(char *s1, char *s2)
{
    char *str;

    if (!s1 && !s2)
        return (0);
    if (!(str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
        return (0);
    if (!s1)
        return (ft_strcpy(str, s2));
    if (!s2)
        return (ft_strcpy(str, s1));
    ft_strcpy(str, s1);
    ft_strcat(str, s2);
    if (s1)
        free(&(s1[0]));
    if (s2)
        free(&(s2[0]));
    return (str);
}