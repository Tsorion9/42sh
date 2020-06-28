/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wordmove_cursor.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:19 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:12:20 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

static void	wordmove_right(void)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(rp(NULL)->user_in);
	while ((i = search_index()) < len)
	{
		if (ft_isspace(rp(NULL)->user_in[i]))
			move_cursor(RIGHT_ARROW);
		else
			break ;
	}
	while ((i = search_index()) < len)
	{
		if (!ft_isspace(rp(NULL)->user_in[i]))
			move_cursor(RIGHT_ARROW);
		else
			break ;
	}
}

static void	wordmove_left(void)
{
	int i;

	while ((i = search_index() - 1) >= 0)
	{
		if (ft_isspace(rp(NULL)->user_in[i]))
			move_cursor(LEFT_ARROW);
		else
			break ;
	}
	while ((i = search_index() - 1) >= 0)
	{
		if (!ft_isspace(rp(NULL)->user_in[i]))
			move_cursor(LEFT_ARROW);
		else
			break ;
	}
}

void		wordmove_cursor(long c)
{
	if (c == CTRL_LEFT)
		wordmove_left();
	else
		wordmove_right();
}
