/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_instruction.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:12:02 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:12:04 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	set_instruction(t_redirect **redirect, t_tokens type)
{
	if (type == GREAT)
		(*redirect)->instruction = OUTPUT_DIRECTION;
	else if (type == LESS)
		(*redirect)->instruction = INPUT_DIRECTION;
	else if (type == DGREAT)
		(*redirect)->instruction = DOUBLE_OUTPUT_DIRECTION;
	else if (type == DLESS)
		(*redirect)->instruction = DOUBLE_INPUT_DERECTION;
	else if (type == GREATAND)
		(*redirect)->instruction = DUPLICAT_OUTPUT;
	else if (type == LESSAND)
		(*redirect)->instruction = DUPLICAT_INPUT;
	else
		(*redirect)->instruction = UNKNOWN_REDIRECT;
	if (need_set_default_fd(IS_NEED_DEFAULT_FD))
	{
		if (type == GREAT || type == DGREAT || type == GREATAND)
			(*redirect)->redirector->fd = STDOUT_FILENO;
		else if (type == LESS || type == DLESS || type == LESSAND)
			(*redirect)->redirector->fd = STDIN_FILENO;
	}
}
