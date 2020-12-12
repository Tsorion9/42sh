/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complete_word.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:10:59 by mphobos           #+#    #+#             */
/*   Updated: 2020/12/12 22:28:05 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int		delete_prev_word(char *user_in, char *remainder_word, int i)
{
	size_t		len;
	t_rp		*trp;

	trp = rp(NULL);
	len = ft_strlen(remainder_word);
	if (i && user_in[i - 1] != ' ' && user_in[i - 1] != '\t' && \
		(user_in[i] == ' ' || user_in[i] == '\t' || user_in[i] == '\0'))
		return (0);
	while (user_in[i + 1] && user_in[i + 1] != ' ' && user_in[i + 1] != '\t')
	{
		move_cursor(RIGHT_ARROW);
		i++;
	}
	move_cursor(RIGHT_ARROW);
	i++;
	while (len--)
	{
		delete_symbol();
		i--;
	}
	return (1);
}

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
		full_word[full_word_len] = '\0';
	full_word[full_word_len + 1] = '\0';
}

void		complete_word2(size_t i, char *remainder_word, char *full_word)
{
	i = ft_strlen(remainder_word);
	if (full_word[i] && \
		delete_prev_word(rp(NULL)->user_in, remainder_word, \
		search_index(rp(NULL)->cur_pos, rp(NULL)->prompt_len)))
		i = 0;
	while (full_word[i])
		add_symbol(full_word[i++]);
}

void		complete_word(t_completion *matches, char *remainder_word,\
		char *path)
{
	size_t		i;
	char		full_word[BUFFSIZE];

	i = 0;
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
	complete_word2(i, remainder_word, full_word);
}
