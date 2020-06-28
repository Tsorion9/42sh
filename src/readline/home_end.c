/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   home_end.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:37 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:37 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void	home_end(long c)
{
	int i;

	i = rp(NULL)->len;
	while (i--)
		move_cursor(c == HOME ? LEFT_ARROW : RIGHT_ARROW);
}
