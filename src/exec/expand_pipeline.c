/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:58:26 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 20:58:27 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static int	expand_filename(t_redirect **redirect)
{
	int			status;
	t_redirect	*tmp;

	status = EXPANSION_SUCCESS;
	tmp = *redirect;
	if (*redirect != NULL)
	{
		while (tmp)
		{
			status = word_expansion(&(tmp->redirector->filename));
			if (status == EXPANSION_FAIL)
				return (status);
			if (status == NEED_FIELD_SPLIT)
			{
				tmp->redirector->need_field_split = NEED_FIELD_SPLIT;
				tmp->redirector->need_quote_rm = 0;
			}
			if (tmp->need_expand_heredoc)
				status = word_expansion(&tmp->heredoc_value);
			tmp = tmp->next;
		}
	}
	return (status);
}

static int	expand_simple_command(t_simple_cmd *simple_cmd)
{
	t_word_list	*words;
	int			status_words;
	int			status_filename;

	words = simple_cmd->words;
	status_filename = expand_filename(&simple_cmd->redirects);
	while (words)
	{
		status_words = word_expansion(&words->word);
		if (status_words == NEED_FIELD_SPLIT)
		{
			words->need_quote_rm = 0;
			words->need_field_split = NEED_FIELD_SPLIT;
		}
		if (status_words == EXPANSION_FAIL || status_filename == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		words = words->next;
	}
	return (EXPANSION_SUCCESS);
}

static int	expand_command(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
	{
		if (expand_simple_command(cmd->simple_cmd) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
	}
	return (EXPANSION_SUCCESS);
}

int			expand_pipeline(t_pipeline *pipeline)
{
	while (pipeline)
	{
		if (expand_command(pipeline->command) == EXPANSION_FAIL)
			return (EXPANSION_FAIL);
		pipeline = pipeline->next;
	}
	return (EXPANSION_SUCCESS);
}
