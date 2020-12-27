/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_word_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:44:58 by nriker            #+#    #+#             */
/*   Updated: 2020/12/27 16:05:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int			check_var_word_dollar(char *line, int i)
{
	if (i && line[i - 1] == '$')
		return (TRUE);
	return (FALSE);
}
