/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc_l.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 02:08:15 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 02:08:16 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_fc.h"

static void		init_start_data(t_fc_options *options, int *first, int *last)
{
	if (!(options->first))
		options->first = FC_OPERAND_FIRST_DEFAULT_VALUE;
	if (!(options->last))
		options->last = options->number_of_history;
	convert_operands_to_pisitive_history_number(options);
	*first = options->first;
	*last = options->last;
	if (options->flags & FC_FLAG_R)
	{
		*first = options->last;
		*last = options->first;
	}
}

static void		print_history_str(t_fc_options *options, int first,
									t_history *history)
{
	if (!(options->flags & FC_FLAG_N))
		ft_printf("%d\t ", first);
	ft_printf("%s\n", history->str);
}

int				exec_fc_l(t_fc_options *options)
{
	t_history	*history;
	int			first;
	int			last;

	init_start_data(options, &first, &last);
	history = get_history(options, first);
	while (first != last)
	{
		if (!(options->flags & FC_FLAG_N))
			ft_printf("%d\t ", first);
		ft_printf("%s\n", history->str);
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
	print_history_str(options, first, history);
	return (1);
}
