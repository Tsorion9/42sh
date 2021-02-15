/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_default_values.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:15:41 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:15:42 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environment.h"

/*
** parameter[:]=[word]
*/

void	assign_default_values(char **src_word, char **word,
							char *param, int have_colon)
{
	size_t	i;
	char	*param_value;

	i = 0;
	param_value = ft_getenv(env, param);
	if (param_value == NULL || (have_colon && param_value == NULL))
	{
		word_expansion(word);
		ft_setenv(env, param, *word);
		replace_value(src_word, *word, &i, ft_strlen(*src_word));
	}
	else
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
}
