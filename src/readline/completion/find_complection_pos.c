/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_complection_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:12:17 by mavan-he          #+#    #+#             */
/*   Updated: 2020/12/28 22:58:59 by nriker           ###   ########.fr       */
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
	if (i == 0 && line[i] != '$')
		return (COM_CMD);
	else if (line[i] == '$')
		return (COM_VAR_WORD_DOLLAR);
	if (check_var_word_brace(line, i) && !check_var_word_dollar(line, i))
		return (COM_VAR_WORD_BRACE);
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
	if (i > 0 && line[i] == '{' && line[i - 1] == '$')
		return (COM_VAR);
	else if (check_var_word_dollar(line, i))
		return (COM_VAR_WORD_DOLLAR);
	return (COM_FILE);
}
