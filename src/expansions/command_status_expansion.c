/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_status_expansion.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:45:05 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 19:45:06 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "exec.h"

/*
** len используется для 2 случаев '$?' и '${?}'
** для '$?' длина заменяемой части 2, для '${?}' 4
*/

void	last_cmd_status_expansion(char **src_word, size_t *i, size_t len)
{
	char	*s_status;

	s_status = ft_itoa(g_last_cmd_status);
	replace_value(src_word, s_status, i, len);
	free(s_status);
}
