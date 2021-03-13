/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:57:02 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 01:57:03 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_fc.h"
#include "exec.h"

static void	init_start_data(t_fc_options *options, int *first, int *last)
{
	if (!(options->first))
		options->first = -1;
	if (!(options->last))
		options->last = options->first;
	convert_operands_to_pisitive_history_number(options);
	*first = options->first;
	*last = options->last;
	if (options->flags & FC_FLAG_R)
	{
		*first = options->last;
		*last = options->first;
	}
}

int			exec_fc_s(t_fc_options *options)
{
	t_history	*history;
	int			first;
	int			last;
	int			status;

	init_start_data(options, &first, &last);
	history = get_history(options, first);
	while (first != last)
	{
		ft_printf("%s\n", history->str);
		status = exec_string(history->str);
		if (first > last)
		{
			first--;
			history = history->next;
		}
		else
		{
			first++;
			history = history->prev;
		}
	}
	ft_printf("%s\n", history->str);
	status = exec_string(history->str);
	return (status);
}
