/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clever_list_to_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 14:20:29 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 14:20:30 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

char			**clever_list_to_array(t_list *l, int *len)
{
	char	**arr;
	char	**ret;

	if (!(arr = ft_memalloc(sizeof(char *) * (ft_lstlen(l) + 1))))
		return (NULL);
	*len = 0;
	ret = arr;
	while (l)
	{
		if (ft_strlen((char *)l->content) == 0)
		{
			l = l->next;
			continue ;
		}
		(*len)++;
		*arr = ft_strdup((char *)l->content);
		l = l->next;
		arr++;
	}
	return (ret);
}
