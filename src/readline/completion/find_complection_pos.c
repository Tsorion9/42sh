/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_complection_pos.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:12:17 by mavan-he          #+#    #+#             */
/*   Updated: 2020/12/12 23:10:38 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static int	is_cmd_seperator(char c)
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
	if (i < 0 || is_cmd_seperator(line[i]) == true)
		return (COM_CMD);
	return (COM_FILE);
}

int			find_complection_pos(char *line, int i)
{
	if (i == 0)
		return (COM_CMD);
	i--;
	while (i >= 0)
	{
		if (is_valid_name_char(line[i]) == false || line[i] == '$')
			break ;
		i--;
	}
	if (i < 0 || is_cmd_seperator(line[i]) == true)
		return (COM_CMD);
	if (line[i] == ' ' || line[i] == '\t')
		return (find_pos_before_space(line, i));
	if (line[i] == '$' || (i > 0 && line[i] == '{' && line[i - 1] == '$'))
		return (COM_VAR);
	return (COM_FILE);
}
