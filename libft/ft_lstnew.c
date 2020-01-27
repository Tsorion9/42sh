/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 19:15:46 by mphobos           #+#    #+#             */
/*   Updated: 2019/10/12 15:12:00 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(const void *content, size_t content_size)
{
	t_list	*ptr;

	if (!(ptr = (t_list*)malloc(sizeof(t_list) * 1)))
		return (NULL);
	ptr->next = NULL;
	if (content == NULL)
	{
		ptr->content = NULL;
		ptr->content_size = 0;
		return (ptr);
	}
	if (!(ptr->content = (void*)malloc(sizeof(content_size))))
	{
		free(ptr);
		return (NULL);
	}
	ft_memcpy(ptr->content, content, content_size);
	ptr->content_size = content_size;
	return (ptr);
}
