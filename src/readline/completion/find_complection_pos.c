/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_complection_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:12:17 by mavan-he          #+#    #+#             */
/*   Updated: 2020/12/26 12:14:21 by nriker           ###   ########.fr       */
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
	if (i < 0 || is_seperator(line[i]) == true)
		return (COM_CMD);
	return (COM_FILE);
}

int			check_var_word(char *line, int i)
{
	int y;

	y = i;
	while (i >= 1 && line[i] != '{' && line[i - 1] != '$')
		i--;
	if (i == 1 && (line[i] != '{' || line[i - 1] != '$'))
		return (false);
	if (y - i == 1)
	{
		while (line[y] != '\0' && line[y] != '}')
			y++;
		if (line[y] == '}')
			return (true);
		return (false);
	}
	while (line[y] != '\0' && line[y] != '}')
		y++;
	if (line[y] == '\0')
	{
		while (y != 0 && line[y] != '}')
			y--;
		if (line[y] == '}')
			return (false);
	}
	return (true);
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
		if (is_valid_name_char(line[i]) == false || line[i] == '$')
			break ;
		i--;
	}
	if (i < 0 || is_seperator(line[i]) == true)
		return (COM_CMD);
	if (line[i] == ' ' || line[i] == '\t')
		return (find_pos_before_space(line, i));
	if (line[i] == '$' || (i > 0 && line[i] == '{' && line[i - 1] == '$'))
		return (COM_VAR);
	return (COM_FILE);
}
