/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:36 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/13 23:45:36 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

char			*word_without_path(char *str_search)
{
	size_t		i;
	char		*new_str;

	new_str = NULL;
	if ((i = ft_strlen(str_search) - 1) < 0)
		return (new_str);
	if (str_search[i] == '\0')
		i--;
	while (i > 0 && str_search[i - 1]  != '/')
		i--;
	if (!(new_str = ft_strdup(str_search + i)))
		return NULL;
	free(str_search);
	return (new_str);
}

t_completion	*ret_matches(t_completion *com_lst, char **str_search)
{
	t_completion	*matches;
	size_t			str_search_len;

	matches = NULL;
	if (ft_strchr(*(str_search), '/'))
		if (!(*(str_search) = word_without_path(*(str_search))))
			return (matches);
	str_search_len = ft_strlen(*(str_search));
	while (com_lst)
	{
		if (!(*str_search) || ft_strnequ(com_lst->str, *(str_search), str_search_len))
			add_new_completion(&matches, com_lst->str);
		com_lst = com_lst->next;
	}
	return (matches);
}
