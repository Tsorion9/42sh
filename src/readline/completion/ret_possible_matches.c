/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ret_possible_matches.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:11:39 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:40 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static int		is_dir(char *file_name, char *path)
{
	char		*full_name;
	struct stat	file_info;

	if (!(full_name = ft_strjoin(file_name, path)))
		exit(1);
	if (!(lstat(full_name, &file_info)))
	{
		free(full_name);
		return (0);
	}
	free(full_name);
	return (S_ISDIR(file_info.st_mode) ? 1 : 0);
}

t_completion	*ret_possible_matches(char *path, int first_word)
{
	DIR				*dp;
	struct dirent	*file_name;
	t_completion	*com_lst;

	if (!path)
		dp = opendir(".");
	else
		dp = opendir(path);
	if (!dp)
		return (NULL);
	com_lst = NULL;
	if (first_word)
	{
		while ((file_name = readdir(dp)))
			if (executable_file(file_name->d_name, path) || \
				is_dir(file_name->d_name, path))
				add_new_completion(&com_lst, file_name->d_name);
	}
	else
		while ((file_name = readdir(dp)))
			add_new_completion(&com_lst, file_name->d_name);
	closedir(dp);
	return (com_lst);
}
