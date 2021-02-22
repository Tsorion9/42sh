/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_alternative_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:13:48 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:13:49 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/*
** parameter[:]+[word]
*/

void	use_alternative_value(char **src_word, char **word,
						char *param_value, int have_colon)
{
	size_t	i;

	if (param_value == NULL || (have_colon && param_value == NULL))
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
	else
	{
		word_expansion(word);
		i = 0;
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
	ft_strdel(word);
}
