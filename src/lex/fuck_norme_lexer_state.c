/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fuck_norme_lexer_state.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:53:44 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 13:53:45 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

/*
** Save or set lexer state after signal
*/

void	fuck_norme_lexer_state(int need_update, char **u_in,\
		int *n_nl, int *ind)
{
	static char	**user_in;
	static int	*need_new_line;
	static int	*index;

	if (need_update)
	{
		ft_memdel((void **)user_in);
		if (u_in)
		{
			*user_in = *u_in;
			*need_new_line = 0;
			return ;
		}
		*need_new_line = 1;
		*index = 0;
	}
	else
	{
		user_in = u_in;
		need_new_line = n_nl;
		index = ind;
	}
}
