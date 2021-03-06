/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 01:53:40 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 01:53:41 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"

static void	fc_print_usage_error(void)
{
	ft_putstr_fd("fc: usage: fc [-e ename] [-lnr] [first] [last] \
		or fc -s [pat=rep] [command]", STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

int			fc_flags_valid(const t_fc_options *options)
{
	int	is_valid;

	is_valid = 1;
	if (options->flags & FC_FLAG_E)
	{
		if ((options->flags & (FC_FLAG_R | FC_FLAG_E)) != \
			(options->flags & FC_SET_ALL_FLAGS))
			is_valid = 0;
	}
	else if (options->flags & FC_FLAG_L)
	{
		if ((options->flags & (FC_FLAG_N | FC_FLAG_R | FC_FLAG_L)) !=
			(options->flags & FC_SET_ALL_FLAGS))
			is_valid = 0;
	}
	else if (options->flags & FC_FLAG_S)
	{
		if ((options->flags & FC_FLAG_S) != (options->flags & FC_SET_ALL_FLAGS))
			is_valid = 0;
	}
	if (!is_valid)
		fc_print_usage_error();
	return (is_valid);
}
