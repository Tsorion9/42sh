/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:10:59 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:11:01 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	change_full_word(char *full_word, char *path)
{
	char		*file_path;
	struct stat	file_info;
	char		lstat_result;
	size_t		full_word_len;

	if (!path || ft_strlen(full_word) == 0)
		lstat_result = lstat(full_word, &file_info);
	else
	{
		file_path = ft_strjoin(path, full_word);
		lstat_result = lstat(file_path, &file_info);
		free(file_path);
	}
	if (lstat_result == -1)
		return ;
	full_word_len = ft_strlen(full_word);
	if (S_ISDIR(file_info.st_mode))
		full_word[full_word_len] = '/';
	else
		full_word[full_word_len] = ' ';
	full_word[full_word_len + 1] = '\0';
}

void		complete_word(t_completion *matches, char *remaider_word,\
		char *path)
{
	size_t		i;
	char		full_word[BUFFSIZE];

	ft_strcpy(full_word, matches->str);
	if (matches->next)
	{
		matches = matches->next;
		while (matches)
		{
			i = 0;
			while (full_word[i] == matches->str[i])
				i++;
			full_word[i] = '\0';
			matches = matches->next;
		}
	}
	else
		change_full_word(full_word, path);
	i = ft_strlen(remaider_word);
	while (full_word[i])
	{
		add_symbol(full_word[i]);
		i++;
	}
}
