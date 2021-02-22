/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_compound_list.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:36:46 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:36:47 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_compound_list(t_compound_list **compound_list)
{
	t_compound_list	*delete;

	while (*compound_list != NULL)
	{
		clean_and_or(&(*compound_list)->and_or);
		delete = *compound_list;
		*compound_list = (*compound_list)->next;
		free(delete);
		delete = NULL;
	}
}
