/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   com_api_get_cursor_position.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:29:05 by nriker            #+#    #+#             */
/*   Updated: 2020/12/13 21:42:13 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int			com_api_get_curs_row(void)
{
	size_t		i;
	size_t		l;
	int			row;
	char		get[50];

	l = 0;
	write(STDIN_FILENO, GETCURSORPOS, 4);
	while (l < 50 - 1 && read(1, get + l, 1) == 1)
	{
		if (get[l] == 'R')
			break ;
		l++;
	}
	i = 1;
	get[l] = '\0';
	while (get[i - 1] != '[' && get[i] != '\0')
		i++;
	if (ft_isdigit(get[i]) == false)
		return (-1);
	row = ft_atoi(&get[i]);
	return (row);
}

int			com_api_get_curs_col(void)
{
	size_t		l;
	int			row;
	char		get[50];

	l = 0;
	write(STDIN_FILENO, GETCURSORPOS, 4);
	while (l < 50 - 1 && read(1, get + l, 1) == 1)
	{
		if (get[l] == 'R')
			break ;
		l++;
	}
	get[l] = '\0';
	row = ft_atoi(ft_strrchr(get, ';') + 1);
	return (row);
}
