/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_complection_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:12:17 by mavan-he          #+#    #+#             */
/*   Updated: 2020/12/26 14:47:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static int	is_seperator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '\n');
}

static int	find_pos_before_space(char *line, int i)
{
	while (i >= 0)
	{
		if (line[i] != ' ' && line[i] != '\t')
			break ;
		i--;
	}
	if (i < 0 || is_seperator(line[i]) == TRUE)
		return (COM_CMD);
	return (COM_FILE);
}

int			find_complection_pos(char *line, int i)
{
	if (i == 0)
		return (COM_CMD);
	if (check_var_word(line, i))
		return (COM_VAR_WORD);
	i--;
	while (i >= 0)
	{
		if (is_valid_name_char(line[i]) == FALSE || line[i] == '$')
			break ;
		i--;
	}
	if (i < 0 || is_seperator(line[i]) == TRUE)
		return (COM_CMD);
	if (line[i] == ' ' || line[i] == '\t')
		return (find_pos_before_space(line, i));
	if (line[i] == '$' || (i > 0 && line[i] == '{' && line[i - 1] == '$'))
		return (COM_VAR);
	return (COM_FILE);
}
