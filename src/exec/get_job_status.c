/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_job_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 02:38:45 by jsance            #+#    #+#             */
/*   Updated: 2021/03/20 02:38:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job.h"

char	*get_job_status(t_job *j)
{
	if (j->state == BACKGROUND)
		return (job_state_tostr(j->state));
	else
		return (job_status_tostr(j->status));
}
