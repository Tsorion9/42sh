/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_list_attributes.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:13:46 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 16:13:47 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command_structs.h"

/*
** Just save attributes from source list to destination list
*/

void	save_list_attributes(t_word_list *src, t_word_list **dest)
{
	t_word_list	*tmp;

	tmp = *dest;
	while (tmp)
	{
		tmp->need_quote_rm = src->need_quote_rm;
		tmp->need_field_split = src->need_field_split;
		tmp = tmp->next;
	}
}
