/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expansion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 19:53:07 by jsance            #+#    #+#             */
/*   Updated: 2021/02/14 19:55:36 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"
#include "environment.h"

void	brace_var_expansion(char **src_word, size_t *i, int skeep_char,
					  int word_state)
{
	size_t	j;
	char	*var_value;
	char	*var_name;

	if (!is_valid_var_name(*src_word))
	{
		ft_fprintf(2, "%s%s\n", E_BAD_SUBSTITUTION, *src_word);
		expasnion_status(EXPANSION_FAIL);
		return ;
	}
	j = *i + skeep_char;
	while ((*src_word)[j] && (is_valid_var_char((*src_word)[j])
							  || (j != 0 && ft_isdigit((*src_word)[j]))))
		j++;
	var_name = ft_strsub(*src_word, *i + skeep_char, j - *i - skeep_char);
	var_value = ft_getenv(env, var_name);
	replace_value(src_word, var_value, i, j - *i);
	free(var_name);
	if (!(word_state & IN_DQUOTE_STATE) && !(word_state & IN_QUOTE_STATE))
		expasnion_status(NEED_FIELD_SPLIT);
}

/*
** word_state is used to check quote states
*/

void	var_expansion(char **src_word, size_t *i, int skeep_char,
					int word_state)
{
	size_t	j;
	char	*var_value;
	char	*var_name;

	j = *i + skeep_char;
	while ((*src_word)[j] && (is_valid_var_char((*src_word)[j])
								|| (j != 0 && ft_isdigit((*src_word)[j]))))
		j++;
	var_name = ft_strsub(*src_word, *i + skeep_char, j - *i - skeep_char);
	var_value = ft_getenv(env, var_name);
	replace_value(src_word, var_value, i, j - *i);
	free(var_name);
	if (!(word_state & IN_DQUOTE_STATE) && !(word_state & IN_QUOTE_STATE))
		expasnion_status(NEED_FIELD_SPLIT);
}
