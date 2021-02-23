/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:29:45 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:29:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_command(t_command **command)
{
	if (!*command)
		return ;
	if ((*command)->cmd_type == SUBSHELL)
		clean_subshell(&(*command)->subshell);
	else if ((*command)->cmd_type == BRACE_GROUP)
		clean_brace_group(&(*command)->brace_group);
	else
		clean_simple_cmd(&(*command)->simple_cmd);
	free(*command);
	*command = NULL;
}

void	clean_pipeline(t_pipeline **pipeline)
{
	t_pipeline	*delete;

	while (*pipeline != NULL)
	{
		clean_command(&(*pipeline)->command);
		delete = *pipeline;
		*pipeline = (*pipeline)->next;
		free(delete);
		delete = NULL;
	}
}

void	clean_and_or(t_andor_list **and_or)
{
	t_andor_list	*delete;

	while (*and_or != NULL)
	{
		clean_pipeline(&(*and_or)->pipeline);
		delete = *and_or;
		*and_or = (*and_or)->next;
		free(delete);
		delete = NULL;
	}
}

void	clean_complete_command(t_complete_cmd **complete_cmd)
{
	t_complete_cmd	*delete;
	t_complete_cmd	*start;

	start = *complete_cmd;
	while (start != NULL)
	{
		clean_and_or(&start->and_or);
		delete = start;
		start = start->next;
		free(delete);
		delete = NULL;
	}
	*complete_cmd = NULL;
}
