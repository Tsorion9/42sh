/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_words_to_assignments.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 20:53:56 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 20:53:57 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "assignment_word.h"

/*
** Mark some words of pipeline as assignment words before execution
*/

static void	words_to_assignments(t_simple_cmd *cmd)
{
	t_word_list *current;
	t_word_list *new;

	current = cmd->words;
	cmd->assignments = NULL;
	while (current)
	{
		if (!looks_like_assignment_word(current->word))
		{
			cmd->words = current;
			break ;
		}
		cmd->words = current->next;
		new = create_word_node(current->word);
		new->need_field_split = current->need_field_split;
		new->need_quote_rm = current->need_quote_rm;
		add_word_to_list(&(cmd->assignments), new);
		free(current->word);
		free(current);
		current = cmd->words;
	}
}

/*
** Other types will be expanded recursively hence they contain SIMPLE_CMD
*/

static void	command_words_to_assignments(t_command *cmd)
{
	if (cmd->cmd_type == SIMPLE_CMD)
	{
		words_to_assignments(cmd->simple_cmd);
	}
}

void		pipeline_words_to_assignments(t_pipeline *pipeline)
{
	while (pipeline)
	{
		command_words_to_assignments(pipeline->command);
		pipeline = pipeline->next;
	}
}
