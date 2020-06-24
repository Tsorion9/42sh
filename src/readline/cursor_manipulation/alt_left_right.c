/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alt_left_right.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:12:02 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:12:02 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		alt_left_right(long c)
{
	int	i;

	i = search_index();
	if (c == ALT_LEFT_ARROW)
		while (i--)
			move_cursor(LEFT_ARROW);
	else
	{
		while (rp(NULL)->user_in[i++])
			move_cursor(RIGHT_ARROW);
	}
}
