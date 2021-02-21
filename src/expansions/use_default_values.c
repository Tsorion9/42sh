/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   use_default_values.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:07:04 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:07:22 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

/*
** parameter[:]-[word]
*/

void	use_default_values(char **src_word, char **word,
						char *param_value, int have_colon)
{
	size_t	i;

	i = 0;
	if (have_colon)
	{
		word_expansion(word);
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
	else
	{
		if (param_value != NULL && !(*param_value))
		{
			ft_strdel(word);
			*word = ft_strnew(0);
			replace_value(src_word, *word, &i, ft_strlen(*src_word));
		}
		else if (param_value == NULL)
		{
			word_expansion(word);
			replace_value(src_word, *word, &i, ft_strlen(*src_word));
		}
	}
	ft_strdel(word);
}
