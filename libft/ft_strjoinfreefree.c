/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfreefree.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 19:53:54 by nriker            #+#    #+#             */
/*   Updated: 2021/01/08 23:01:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfreefree(char *s1, char *s2)
{
    char *str;

    if (s1 == NULL && s2 == NULL)
        return (NULL);
    if ((str = ft_strnew(ft_strlen(s1) + ft_strlen(s2))) == NULL)
        return (NULL);
    if (s1 == NULL)
        return (ft_strcpy(str, s2));
    if (s2 == NULL)
        return (ft_strcpy(str, s1));
    ft_strcpy(str, s1);
    ft_strcat(str, s2);
    if (s1)
        free(s1);
    if (s2)
        free(s2);
    return (str);
}