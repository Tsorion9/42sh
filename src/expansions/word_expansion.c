/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 19:57:20 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 19:57:21 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "expansions.h"

static void	word_expansion_loop(char **src_word, size_t i, int word_state,
								int inside_assign_word)
{
	while ((*src_word)[i] && expasnion_status(GET_STATUS) != EXPANSION_FAIL)
	{
		if (word_state == 0 && (*src_word)[i] == '=')
			inside_assign_word = 1;
		if ((*src_word)[i] == '~')
			try_tilde_expansion(src_word, &i, word_state, inside_assign_word);
		else if ((*src_word)[i] == '\\')
			i += 2;
		else if ((*src_word)[i] == '"')
		{
			word_state ^= IN_DQUOTE_STATE;
			i++;
		}
		else if ((*src_word)[i] == '\'')
		{
			if (!(word_state & IN_DQUOTE_STATE))
				i += find_closing_quote(*src_word + i) + 1;
			else
				i++;
		}
		else if ((*src_word)[i] == '$')
			dollar_expansion(src_word, &i, word_state);
		else
			i++;
	}
}

/*
** source_word malloced
*/

int			word_expansion(char **source_word)
{
	size_t		i;
	int			word_state;
	int			inside_assignment_word;

	if ((*source_word) == NULL || !(**source_word))
		return (EXPANSION_EMPTY_WORD);
	expasnion_status(EXPANSION_SUCCESS);
	i = 0;
	word_state = 0;
	inside_assignment_word = 0;
	word_expansion_loop(source_word, i, word_state, inside_assignment_word);
	return (expasnion_status(GET_STATUS));
}
