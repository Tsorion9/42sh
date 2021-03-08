/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_history_search.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 16:00:04 by mphobos           #+#    #+#             */
/*   Updated: 2021/03/08 16:00:05 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	set_history_search_mode(void)
{
	rp(NULL)->history_search.history_search_mode = 1;
	rp(NULL)->history_search.index = rp(NULL)->index + 1;
}

int		now_search_history(void)
{
	return (rp(NULL)->history_search.history_search_mode);
}
