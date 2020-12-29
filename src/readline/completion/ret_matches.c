/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_matches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:36 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/29 21:08:34 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

char			*word_without_path(char *str_search)
{
	size_t		i;
	char		*new_str;

	new_str = NULL;
	i = ft_strlen(str_search) - 1;
	if (str_search[i] == '\0')
		i--;
	if (str_search[i] != '/')
		while (i > 0 && str_search[i - 1] != '/')
			i--;
	else
	{
		free(str_search);
		return (new_str);
	}
	if (!(new_str = ft_strdup(str_search + i)))
		return (NULL);
	free(str_search);
	return (new_str);
}

t_completion	*ret_matches(t_completion *com_lst, char **str_search)
{
	t_completion	*matches;
	size_t			str_search_len;

	matches = NULL;
	if (ft_strchr(*(str_search), '/'))
		*(str_search) = word_without_path(*(str_search));
	str_search_len = ft_strlen(*(str_search));
	while (com_lst)
	{
		if (!(*str_search) ||
			ft_strnequ(com_lst->str, *(str_search), str_search_len))
		{
			add_new_completion(&matches, com_lst->str);
		}
		com_lst = com_lst->next;
	}
	return (matches);
}
