/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_quote_removal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:28:55 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:28:56 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	quote_removal_filename(t_redirect **redirect)
{
	t_redirect	*tmp;

	tmp = *redirect;
	while (tmp && tmp->redirector->need_quote_rm)
	{
		quote_removal(&(tmp->redirector->filename));
		tmp = tmp->next;
	}
}

static void	simple_command_quote_removal(t_simple_cmd *cmd)
{
	t_word_list *words;
	t_word_list *assign;

	words = cmd->words;
	assign = cmd->assignments;
	quote_removal_filename(&cmd->redirects);
	while (words)
	{
		if (words->need_quote_rm)
			quote_removal(&words->word);
		words = words->next;
	}
	while (assign)
	{
		if (assign->need_quote_rm)
			quote_removal(&assign->word);
		assign = assign->next;
	}
}

static void	command_quote_removal(t_command *command)
{
	if (command->cmd_type == SIMPLE_CMD)
		simple_command_quote_removal(command->simple_cmd);
}

void		pipeline_quote_removal(t_pipeline *pipeline)
{
	t_pipeline *tmp;

	tmp = pipeline;
	while (tmp)
	{
		command_quote_removal(tmp->command);
		tmp = tmp->next;
	}
}
