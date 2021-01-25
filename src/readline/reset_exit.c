/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 20:18:17 by anton             #+#    #+#             */
/*   Updated: 2021/01/09 21:47:43 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"
#include "inc21sh.h"
#include "job.h"

void		reset_exit(int status)
{
	/* static int notified; */

	if (isatty(0))
	{
		/* TODO: (this can be called from parser)
		if (top_level_shell && ft_lstlen(jobs) && !notified)
		{
			ft_printf("There are stopped or running jobs\n");
			notified = 1;
			return ;
		}
		*/

		reset_input_mode();
		back_to_start_history_rp();
		save_in_file_history(rp(NULL)->history);
	}
	exit(status);
}
