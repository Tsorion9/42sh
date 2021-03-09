/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   indicate_error_if_null_or_unset.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:10:10 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:10:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environment.h"

/*
** parameter[:]?[word]
*/

void	indicate_error_if_null_or_unset(char **src_word, char **word,
										char *param, int have_colon)
{
	char	*param_value;

	param_value = ft_getenv(g_env, param);
	if (param_value != NULL && *param_value == '\0' && !have_colon)
	{
		free(*src_word);
		*src_word = ft_strnew(0);
	}
	else
	{
		if (**word != '\0')
			word_expansion(word);
		ft_fprintf(STDERR_FILENO, "42sh: %s: %s\n", param,
					(**word == '\0') ? E_PARAM_NULL_OR_UNSET : *word);
		if (**word != '\0')
			expasnion_status(EXPANSION_SUCCESS);
		else
			expasnion_status(EXPANSION_FAIL);
	}
	ft_strdel(word);
}
