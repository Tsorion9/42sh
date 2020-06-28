/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 01:29:39 by anton             #+#    #+#             */
/*   Updated: 2020/06/24 01:37:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	step_normal_state(char **pos, int *state)
{
	if (**pos == '\'')
	{
		*state = '\'';
		ft_strcpy(*pos, *pos + 1);
	}
	else if (**pos == '\"')
	{
		*state = '\"';
		ft_strcpy(*pos, *pos + 1);
	}
	else if (**pos == '\\')
	{
		ft_strcpy(*pos, *pos + 1);
		(*pos)++;
	}
	else
		(*pos)++;
}

static void	step_single_quote(char **pos, int *state)
{
	if (**pos == '\'')
	{
		*state = 0;
		ft_strcpy(*pos, *pos + 1);
		return ;
	}
	*pos += 1;
}

static void	step_double_quote(char **pos, int *state)
{
	if (**pos == '\\')
	{
		if (*(*pos + 1) == '\"')
		{
			ft_strcpy(*pos, *pos + 1);
			*pos += 1;
			return ;
		}
		*pos += 1;
		return ;
	}
	if (**pos == '\"')
	{
		*state = 0;
		ft_strcpy(*pos, *pos + 1);
		return ;
	}
	*pos += 1;
}

/*
** Remove all the quotes and '\' in-place
*/

void		remove_quotes(char *s)
{
	char	*pos;
	int		state;

	state = 0;
	pos = s;
	while (*pos)
	{
		if (!state)
			step_normal_state(&pos, &state);
		else if (state == '\'')
			step_single_quote(&pos, &state);
		else if (state == '\"')
			step_double_quote(&pos, &state);
	}
}
