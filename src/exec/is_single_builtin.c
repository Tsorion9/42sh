/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_single_builtin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:21:34 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:21:35 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "t_builtin.h"
#include "exec.h"

int	is_single_builtin(t_pipeline *pipeline)
{
	t_word_list *words;

	if (!pipeline->next)
	{
		if (pipeline->command->cmd_type == SIMPLE_CMD)
		{
			words = pipeline->command->simple_cmd->words;
			if (words && get_builtin(words->word))
			{
				return (1);
			}
		}
		return (0);
	}
	return (0);
}

int	exec_single_builtin(t_pipeline *pipeline)
{
	return (exec_cmd(pipeline->command));
}
