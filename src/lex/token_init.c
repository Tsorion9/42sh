/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 02:05:18 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 02:05:35 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

/*
** returns a initialized copy of the next token
*/

t_token			*copy_init_token(t_token t)
{
	t_token	*copy;

	copy = xmalloc(sizeof(t_token));
	*copy = t;
	if (copy->token_type != word &&\
			copy->token_type != ass_word &&\
			copy->token_type != number)
		copy->attribute = NULL;
	return (copy);
}

t_token			*new_eof(void)
{
	t_token	*t_eof;

	t_eof = xmalloc(sizeof(t_token));
	t_eof->token_type = eof;
	t_eof->attribute = NULL;
	return (t_eof);
}
