/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fc_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 02:44:00 by jsance            #+#    #+#             */
/*   Updated: 2021/03/20 02:44:02 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin_fc.h"
#include "readline.h"

void	loop_fc_args(t_fc_options *options, char **args, int *error_code)
{
	size_t	i;

	i = 1;
	while ((*args)[i] && *error_code == FC_NO_ERROR)
	{
		if ((*args)[i] == 'e')
		{
			options->flags |= FC_FLAG_E;
			args++;
			parse_editor(options, *args, error_code);
			break ;
		}
		else if ((*args)[i] == 'r')
			options->flags |= FC_FLAG_R;
		else if ((*args)[i] == 'l')
			options->flags |= FC_FLAG_L;
		else if ((*args)[i] == 's')
			options->flags |= FC_FLAG_S;
		else if ((*args)[i] == 'n')
			options->flags |= FC_FLAG_N;
		else
			*error_code = FC_USAGE_ERROR;
		i++;
	}
}
