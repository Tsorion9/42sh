/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tail.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:24:30 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:24:31 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_structs.h"

t_word_list	*get_tail(t_word_list *list)
{
	t_word_list *tmp;

	if (list == NULL)
		return (NULL);
	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
