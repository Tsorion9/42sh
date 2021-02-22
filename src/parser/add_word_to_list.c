/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_word_to_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:57:25 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:57:26 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	add_word_to_list(t_word_list **word_list, t_word_list *word)
{
	if (*word_list == NULL)
		*word_list = word;
	else
		add_word_to_list(&(*word_list)->next, word);
}
