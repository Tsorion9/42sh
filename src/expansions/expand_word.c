/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:38 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "remove_quotes.h"
#include "inc21sh.h"
#include "step_quote.h"
#include "replace.h"

static void	step_norm(char **s, int *position, t_exp_state *state)
{
	if ((*s)[*position] == '\\')
	{
		*position += 2;
		return ;
	}
	if ((*s)[*position] == '\'')
	{
		*state = in_sqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '\"')
	{
		*state = in_dqt;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '~' || (*s)[*position] == '$')
	{
		replace(s, position);
		return ;
	}
	(*position)++;
}

/*
** 1) Skip everything inside ''; or \$ or \~
** 2) Expand all the symbols one by one (do not apply expansions to the result
** of expansions)
** Implemented as FSM.
**
** STRING MUST BE VALID!!!! no unpaired quotes ; no quoted '0'
*/

char		*expand_word(char *s)
{
	t_exp_state	state;
	int			position;

	state = norm;
	position = 0;
	while (s[position])
	{
		if (state == norm)
			step_norm(&s, &position, &state);
		else if (state == in_sqt)
			step_single_quote(s, &position, &state);
		else
			step_double_quote(&s, &position, &state);
	}
	remove_quotes(s);
	return (s);
}
