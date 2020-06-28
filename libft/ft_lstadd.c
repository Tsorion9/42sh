/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:47:49 by bgian             #+#    #+#             */
/*   Updated: 2019/10/01 00:16:00 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (!new)
		return ;
	new->next = *alst;
	*alst = new;
}

int		ft_lstadd_data(t_list **lst, void *content, size_t content_size)
{
	t_list	*new;

	new = ft_lstnew_inplace(content, content_size);
	if (!new)
		return (0);
	ft_lstadd(lst, new);
	return (1);
}
