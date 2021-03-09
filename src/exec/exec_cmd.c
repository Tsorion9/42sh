/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 21:14:32 by jsance            #+#    #+#             */
/*   Updated: 2021/03/09 21:14:33 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "parser.h"

int	exec_cmd(t_command *cmd)
{
	if (!cmd->simple_cmd)
	{
		ft_fprintf(2, "%s\n", "Only simple commands implemented yet");
		exit(-1);
	}
	return (exec_simple_cmd(cmd->simple_cmd));
}
