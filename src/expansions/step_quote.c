/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   step_quote.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:39 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "remove_quotes.h"
#include "inc21sh.h"
#include "replace.h"

void	step_single_quote(char *s, int *position, t_exp_state *state)
{
	if (s[*position] == '\'')
		*state = norm;
	else if (s[*position] == '\\')
		(*position)++;
	(*position)++;
}

void	step_double_quote(char **s, int *position, t_exp_state *state)
{
	if ((*s)[*position] == '\"')
		*state = norm;
	else if ((*s)[*position] == '\\')
		(*position)++;
	else if ((*s)[*position] == '$')
	{
		replace(s, position);
		return ;
	}
	(*position)++;
}
