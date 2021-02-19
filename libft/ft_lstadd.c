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

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *tmp;

	if (!new)
		return ;
	if (!*alst)
	{
		*alst = new;
		return ;
	}
	tmp = *alst;
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

int		ft_lstadd_data_back(t_list **lst, void *content, size_t content_size)
{
	t_list	*new;

	(void) content_size;
	new = ft_lstnew_inplace(content, content_size);
	ft_lstadd_back(lst, new);
	return (1);
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

t_list	*ft_lstappend(t_list *lst, void const *content, size_t content_size)
{
	t_list	*new;
	t_list	*tmp;

	if (!content_size || !content || !(new = ft_lstnew(content, content_size)))
		return (lst);
	if (!lst)
		return (new);
	tmp = lst;
	while (lst->next)
		lst = lst->next;
	lst->next = new;
	return (tmp);
}
