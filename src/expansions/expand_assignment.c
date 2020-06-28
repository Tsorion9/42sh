/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_assignment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:38 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "remove_quotes.h"
#include "inc21sh.h"
#include "replace.h"
#include "step_quote.h"

static void	step_norm_assignemt_sup(char **s, int *position, t_exp_state *state)
{
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

static void	step_norm_assignemt(char **s, int *position, t_exp_state *state, \
			int *equal_sign_detected)
{
	if ((*s)[*position] == '=' && !*equal_sign_detected)
	{
		*equal_sign_detected = 1;
		*position += 1;
		return ;
	}
	if ((*s)[*position] == '~' && *equal_sign_detected && *position > 0 && \
		((*s)[*position - 1] == '=' || (*s)[*position - 1] == ':'))
	{
		replace(s, position);
		return ;
	}
	if ((*s)[*position] == '\\')
	{
		*position += 2;
		return ;
	}
	step_norm_assignemt_sup(s, position, state);
}

char		*expand_assignment(char *s)
{
	t_exp_state		state;
	int				position;
	int				equal_sign_detected;

	equal_sign_detected = -1;
	state = norm;
	position = 0;
	while (s[position])
	{
		if (state == norm)
			step_norm_assignemt(&s, &position, &state, &equal_sign_detected);
		else if (state == in_sqt)
			step_single_quote(s, &position, &state);
		else
			step_double_quote(&s, &position, &state);
	}
	return (s);
}
