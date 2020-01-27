/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 21:29:19 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/12 17:22:25 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*ptr;
	t_list	*newlst;
	t_list	*res;

	ptr = f(lst);
	newlst = lst;
	res = ptr;
	if (lst == NULL || f == NULL || ptr == NULL)
		return (NULL);
	while (newlst->next != NULL)
	{
		ptr->next = f(newlst->next);
		if (ptr->next == NULL)
		{
			free(ptr);
			return (NULL);
		}
		newlst = newlst->next;
		ptr = ptr->next;
	}
	ptr->next = NULL;
	return (res);
}
