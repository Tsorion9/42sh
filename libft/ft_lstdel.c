/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 17:28:44 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/12 18:10:02 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*ptr;
	t_list	*prevptr;

	if (*alst == NULL || del == NULL)
		return ;
	while ((*alst)->next != NULL)
	{
		prevptr = *alst;
		ptr = (*alst)->next;
		while (ptr->next != NULL)
		{
			prevptr = prevptr->next;
			ptr = ptr->next;
		}
		del(ptr->content, ptr->content_size);
		free(ptr);
		prevptr->next = NULL;
	}
	del((*alst)->content, (*alst)->content_size);
	*alst = NULL;
}
