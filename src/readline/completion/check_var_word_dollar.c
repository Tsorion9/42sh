/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_word_dollar.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 15:44:58 by nriker            #+#    #+#             */
/*   Updated: 2020/12/28 23:26:05 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int			check_space_in_var_word_dollar(char *line, int i, int y)
{
	if (y && line[y] == ' ' && ft_isalpha(line[y - 1]))
		y--;
	while (y > i)
	{
		if (line[y] == ' ' || line[i] == '\n' || line[i] == '\t')
			return (TRUE);
		y--;
	}
	return (FALSE);
}

int			check_symb_in_var_word_dollar(char *line, int i)
{
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '$')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int			check_var_word_dollar(char *line, int i)
{
	int y;

	y = i;
	if (line[i] == '$')
		return (TRUE);
	while (i > 0)
	{
		if (line[i] == '$')
			break ;
		i--;
	}
	if (line[i] != '$')
		return (FALSE);
	if ((y - i == 1 && !check_symb_in_var_word_dollar(line, i + 1))
		|| !check_space_in_var_word_dollar(line, i, y))
	{
		return (TRUE);
	}
	return (FALSE);
}
