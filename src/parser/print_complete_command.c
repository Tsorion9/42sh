/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_complete_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 21:40:46 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 21:40:47 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_separator_op(t_separator_op separator)
{
	if (separator == OP_NONE)
		return ("NONE");
	else if (separator == OP_SEMICOL)
		return (";");
	else if (separator == OP_BG)
		return ("&");
	else
		return ("UNKNOWN");
}

char	*get_type_if(t_type_andor type)
{
	if (type == ANDOR_NONE)
		return ("NONE");
	else if (type == ANDOR_OR)
		return ("||");
	else if (type == ANDOR_AND)
		return ("&&");
	else
		return ("UNKNOWN");
}

void	print_and_or(t_andor_list *and_or)
{
	t_andor_list	*tmp;
	char			*s;

	tmp = and_or;
	s = "exit status";
	while (tmp)
	{
		ft_printf("\e[0;32m%14s = %d\n", s, tmp->exit_status);
		ft_printf("\e[0;32m%10s     = %s\n", "type if",
						get_type_if(tmp->type_andor));
		print_pipeline(tmp->pipeline);
		tmp = tmp->next;
	}
}

void	print_complete_command(t_complete_cmd *complete_cmd)
{
	t_complete_cmd	*tmp;

	ft_printf("##########print DEBUG info##########\n");
	tmp = complete_cmd;
	while (tmp)
	{
		ft_printf("\e[0;31mSeparator = %s\n",
							get_separator_op(tmp->separator_op));
		print_and_or(tmp->and_or);
		tmp = tmp->next;
	}
}
