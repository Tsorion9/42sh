/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:39 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "remove_quotes.h"
#include "inc21sh.h"
#include "step_quote.h"

/*
** Decide whether to replace dollar or tilda.
** Create new string with replacement
** Free original, update *s
** Increment *pos so that it points to the next char after replacement
*/

void	replace(char **s, int *position)
{
	if ((*s)[*position] == '$')
		expand_dollar(s, position);
	else if ((*s)[*position] == '~')
		expand_tilda(s, position);
}
