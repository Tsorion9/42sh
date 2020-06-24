/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:36 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:36 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

t_completion	*ret_matches(t_completion *com_lst, char *str_search)
{
	t_completion	*matches;
	size_t			str_search_len;

	matches = NULL;
	str_search_len = ft_strlen(str_search);
	while (com_lst)
	{
		if (ft_strnequ(com_lst->str, str_search, str_search_len))
			add_new_completion(&matches, com_lst->str);
		com_lst = com_lst->next;
	}
	return (matches);
}
