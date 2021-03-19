/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:16:40 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 22:16:41 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char		*words_str(t_word_list *words)
{
	size_t		len;
	char		*str_words;
	char		*tmp_str;
	char		*word;
	t_word_list	*tmp;

	tmp = words;
	len = 0;
	str_words = ft_strnew(0);
	while (tmp)
	{
		len += ft_strlen(tmp->word);
		word = ft_strdup(tmp->word);
		tmp_str = ft_strjoinfreefree(str_words, word);
		if (tmp->next)
			tmp_str = ft_strjoinfreefree(tmp_str, ft_strdup(" "));
		str_words = tmp_str;
		tmp = tmp->next;
	}
	return (str_words);
}

char		*simple_cmd_str(t_simple_cmd *cmd)
{
	char		*words;
	char		*redirects;
	char		*res;

	words = words_str(cmd->words);
	redirects = redirects_str(cmd->redirects);
	if (redirects != NULL)
	{
		words = ft_strjoinfreefree(words, ft_strdup(" "));
		res = ft_strjoinfreefree(words, redirects);
		return (res);
	}
	return (words);
}

static void	andor_join_and_clean(char **res, char *andor)
{
	char		*tmp;

	tmp = *res;
	*res = ft_strjoin(*res, andor);
	free(tmp);
}

char		*andor_to_str(t_andor_list *andor)
{
	char		*res;
	char		*tmp;
	char		*res1;

	res = get_pipeline_str(andor->pipeline);
	while (andor->next)
	{
		if (andor->type_andor == ANDOR_AND)
			andor_join_and_clean(&res, " && ");
		if (andor->type_andor == ANDOR_OR)
			andor_join_and_clean(&res, " || ");
		andor = andor->next;
		if (!andor)
			break ;
		tmp = get_pipeline_str(andor->pipeline);
		res1 = ft_strjoin(res, tmp);
		free(res);
		res = res1;
		free(tmp);
	}
	return (res);
}
