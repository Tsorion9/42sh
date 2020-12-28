/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var_word_brace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 14:47:16 by nriker            #+#    #+#             */
/*   Updated: 2020/12/28 20:46:38 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int			check_brace_in_var_word(char *line, int i)
{
	int		y;
	int		sum_brace;
	int		pos_dollar_brace;

	y = i;
	sum_brace = 1;
	pos_dollar_brace = 0;
	while (i != 0)
	{
		if (line[i] == '{' && line[i - 1] == '$')
			pos_dollar_brace = i;
		i--;
	}
	i = pos_dollar_brace;
	while (++i <= y && line[i] != '\0')
	{
		if (line[i] == '}')
			sum_brace--;
		else if (line[i] == '{')
			sum_brace++;
	}
	if (sum_brace > 0)
		return (TRUE);
	return (FALSE);
}

int			check_space_in_var_word(char *line, int i, int y)
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

int			check_symb_in_var_word(char *line, int i)
{
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\0')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int			check_var_word_brace(char *line, int i)
{
	int y;

	y = i;
	while (i >= 1)
	{
		if (line[i] == '{' && line[i - 1] == '$')
			break ;
		i--;
	}
	if (line[i] != '{' || line[i - 1] != '$')
		return (FALSE);
	if ((y - i == 1 && !check_symb_in_var_word(line, i + 1))
        || !check_space_in_var_word(line, i, y))
	{
		while (line[y] != '\0' && line[y] != '}')
			y++;
		if (line[y] == '}')
			return (TRUE);
		return (FALSE);
	}
	if (check_brace_in_var_word(line, y))
		return (TRUE);
	return (FALSE);
}
