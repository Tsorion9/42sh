/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:48:43 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 01:48:44 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_fc.h"
#include "exec.h"

static void	init_fc_options(t_fc_options *options, t_env env, int subshell)
{
	(void)env;
	(void)subshell;
	options->flags = 0;
	options->first = 0;
	options->last = 0;
	ft_memset(options->editor, 0, FC_MAX_EDITOR_NAME_SIZE);
	if (ft_strlen(FC_DEFAULT_EDITOR) <= FC_MAX_EDITOR_NAME_SIZE)
		ft_strcpy(options->editor, FC_DEFAULT_EDITOR);
}

static void	init_fc_history(t_fc_options *options)
{
	t_history	*history;

	history = rp(NULL)->history;
	while (history && history->prev)
		history = history->prev;
	if (((options->flags & FC_FLAG_S) || (options->flags & FC_FLAG_E) ||
		!(options->flags)) && history && history->next)
		delete_history(history->next);
	options->number_of_history = 0;
	while (history && history->next)
	{
		history = history->next;
		options->number_of_history++;
	}
	options->history_first = history;
}

void		convert_operands_to_pisitive_history_number(t_fc_options *options)
{
	if (options->first > options->number_of_history)
		options->first = options->number_of_history;
	if (options->last > options->number_of_history)
		options->last = options->number_of_history;
	if (options->first < 0)
	{
		options->first = options->number_of_history + options->first + 1;
		if (options->first < 1)
			options->first = 1;
	}
	if (options->last < 0)
	{
		options->last = options->number_of_history + options->last + 1;
		if (options->last < 1)
			options->last = 1;
	}
	if (!options->first)
		options->first = -1;
	if (!options->last)
		options->last = -1;
}

t_history	*get_history(t_fc_options *options, int history_number)
{
	t_history *history;

	history = options->history_first;
	while (history && history->prev
					&& history->prev->prev
					&& history_number > 1)
	{
		history = history->prev;
		history_number--;
	}
	return (history);
}

int			builtin_fc(char **args, t_env env, int subshell)
{
	t_fc_options	options;
	int				error_code;

	if (!isatty(STDIN_FILENO))
		return (FC_NO_ERROR);
	error_code = FC_NO_ERROR;
	init_fc_options(&options, env, subshell);
	args = parse_fc_flags_and_editor(&options, args, &error_code);
	init_fc_history(&options);
	if (!options.number_of_history)
		return (error_code);
	if (error_code != FC_NO_ERROR)
		return (error_code);
	if (!fc_flags_valid(&options))
		return (error_code);
	parse_fc_operands(&options, args, &error_code);
	if (error_code != FC_NO_ERROR)
		return (error_code);
	if (options.flags & FC_FLAG_L)
		return (exec_fc_l(&options));
	else if (options.flags & FC_FLAG_S)
		return (exec_fc_s(&options));
	else if (options.flags & FC_FLAG_E || !options.flags)
		return (exec_fc_e(&options));
	return (error_code);
}
