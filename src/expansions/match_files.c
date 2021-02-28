/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 13:40:14 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 13:40:15 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "expansions.h"

static void		*make_new_data(char *current_path, char *new_component)
{
	char	*tmp;
	char	*res;

	if (ft_strequ(current_path, "."))
	{
		if (ft_strequ(new_component, ".") || ft_strequ(new_component, ".."))
		{
			tmp = ft_strdup("");
			res = ft_path_append(new_component, tmp);
			free(tmp);
			return (res);
		}
		return (ft_strdup(new_component));
	}
	return (ft_path_append(current_path, new_component));
}

static t_list	*search_dir(char *current_path, char *new_component)
{
	char			*is_unquoted;
	DIR				*d;
	struct dirent	*entry;
	t_list			*matches;
	char			*new_data;

	d = opendir(current_path);
	if (!d)
		return (NULL);
	matches = NULL;
	is_unquoted = pattern_quote_removal(&new_component);
	while ((entry = readdir(d)))
	{
		if (*(entry->d_name) == '.' && *new_component != '.')
			continue ;
		if (ft_clever_match(entry->d_name, new_component, is_unquoted))
		{
			new_data = make_new_data(current_path, entry->d_name);
			ft_lstadd_data(&matches, new_data, 0);
		}
	}
	free(is_unquoted);
	closedir(d);
	return (matches);
}

void			match_files(t_list **matches, char **path_components,
							char *current_path)
{
	t_list *new_matches;
	t_list *current;

	if (!path_components[0])
	{
		ft_lstadd_data(matches, ft_strdup(current_path), 0);
		return ;
	}
	new_matches = search_dir(current_path, path_components[0]);
	if (!new_matches)
		return ;
	current = new_matches;
	while (current)
	{
		match_files(matches, path_components + 1, (char *)current->content);
		current = current->next;
	}
	ft_lstdel(&new_matches, del_list);
}
