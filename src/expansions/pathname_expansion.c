/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathname_expansion.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:29:20 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 13:29:21 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "libft.h"
#include "expansions.h"
#include "environment.h"
#include "parser.h"

static int		starts_from_root(const char *word)
{
	char	*dup;
	char	*info;
	int		res;

	dup = ft_strdup(word);
	info = pattern_quote_removal(&dup);
	free(info);
	res = (*dup == '/');
	free(dup);
	return (res);
}

/*
** Return malloced 2d dimensional array of words
*/

char			**pathname_expansion(char *word)
{
	char	**path_components;
	char	**res;
	t_list	*matches;
	char	*current_path;
	int		len;

	matches = NULL;
	path_components = path_clever_split(word);
	if (path_components && !path_components[0])
	{
		del_array(path_components);
		return (NULL);
	}
	current_path = starts_from_root(word) ? ft_strdup("/") : ft_strdup(".");
	match_files(&matches, path_components, current_path);
	res = clever_list_to_array(matches, &len);
	qsort_void_ptr((void **)res, len, is_greater);
	del_array(path_components);
	ft_lstdel(&matches, del_list);
	free(current_path);
	return (res);
}

t_word_list		*pathname_expansion_list(char *word)
{
	char		**res;
	t_word_list	*fields;
	t_word_list *tmp;
	int			i;

	res = pathname_expansion(word);
	if (!res)
		return (NULL);
	if (!res[0])
	{
		del_array(res);
		return (NULL);
	}
	fields = create_word_node(res[0]);
	tmp = fields;
	i = 0;
	while (res[++i])
	{
		tmp->next = create_word_node(res[i]);
		tmp = tmp->next;
	}
	del_array(res);
	return (fields);
}
