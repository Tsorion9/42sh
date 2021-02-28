/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_set_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:18:31 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 12:18:32 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void		retrieve_brace(t_lexer_state *token)
{
	if (token->brace_buf)
	{
		if ((CURRENT_CHAR == '}' || CURRENT_CHAR == ')')
			&& token->brace_buf->quoted
			&& token->flags & DQUOTE_STATE)
			pop(token, CURRENT_CHAR);
		if ((CURRENT_CHAR == '}' || CURRENT_CHAR == ')')
			&& (token->flags & QUOTE_STATE) == 0
			&& (token->flags & DQUOTE_STATE) == 0
			&& token->brace_buf->quoted == 0)
			pop(token, CURRENT_CHAR);
	}
}

void			lexer_set_flags(t_lexer_state *token)
{
	if (is_spec(CURRENT_CHAR))
		token->flags |= HAS_SPECIAL;
	if (CURRENT_CHAR == '"' && (token->flags & QUOTE_STATE) == 0)
		token->flags ^= DQUOTE_STATE;
	if (CURRENT_CHAR == '\'' && (token->flags & DQUOTE_STATE) == 0)
		token->flags ^= QUOTE_STATE;
	retrieve_brace(token);
	if ((token->flags & ISOPEN_STATE) == 0 && (token->brace_buf != NULL
		|| (token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE)))
		token->flags ^= ISOPEN_STATE;
	else if (token->flags & ISOPEN_STATE && token->brace_buf == NULL
		&& !(token->flags & QUOTE_STATE) && !(token->flags & DQUOTE_STATE))
		token->flags ^= ISCLOSED_STATE;
}
