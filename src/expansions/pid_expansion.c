/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:40:49 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 19:41:18 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/*
** The getpid() function are always successful, and no return
** value is reserved to indicate an error.
*/

void	pid_expansion(char **src_word, size_t *i)
{
	int		pid;
	char	*s_pid;

	pid = getpid();
	s_pid = ft_itoa(pid);
	replace_value(src_word, s_pid, i, 2);
	free(s_pid);
}
