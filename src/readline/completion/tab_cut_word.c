/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_cut_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 18:05:50 by alexbuyanov       #+#    #+#             */
/*   Updated: 2020/10/17 18:24:28 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int		tab_check_space(char *user_in, int i)
{
	if (i && user_in[i - 1] == ' ' && user_in[i] == ' ')
		return (1);
	return (0);
}

int			check_point_slesh(char *line, int x)
{
	int k;

	k = x;
	if (line[k] == '.')
	{
		k++;
		if (line[k] == '.')
			k++;
		if (line[k] != '/')
			return (x);
		while (line[k] == '/' && line[k])
			k++;
		return (k);
	}
	return (x);
}

char	*tab_cut_word(char *user_in, int i)
{
	char	*line;
	int		x;
	int		sx;
	int		sy;

	line = user_in;
	x = i;
	if (!ft_strlen(line) || (!x && line[x] == ' '))
		return (NULL);
	if (line[x] != ' ' || (line[x - 1] != ' '))
	{
		while (x > 0 && line[x - 1] != '\t' && line[x - 1] != ' ' \
			&& line[x - 1] != '|' && user_in[x - 1] != '&')
			x--;
		x = check_point_slesh(line, x);
		sx = x;
		while (line[x] != '\t' && line[x] != ' ' && line[x])
			x++;
		sy = x;
		line = ft_strnew(sy - sx);
		line = ft_strncpy(line, user_in + sx, sy - sx);
		return (line);
	}
	return (NULL);
}
