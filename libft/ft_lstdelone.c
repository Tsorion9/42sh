/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:47:21 by bgian             #+#    #+#             */
/*   Updated: 2019/10/09 18:36:31 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Delete first element. *alst points to second.
*/

void	ft_lstdelone(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*second;

	second = (*alst)->next;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = second;
}
