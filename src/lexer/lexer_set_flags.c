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
		if ((token->value[token->str_index] == '}'
			|| token->value[token->str_index] == ')')
			&& token->brace_buf->quoted
			&& token->flags & DQUOTE_STATE)
			pop(token, token->value[token->str_index]);
		if ((token->value[token->str_index] == '}'
			|| token->value[token->str_index] == ')')
			&& (token->flags & QUOTE_STATE) == 0
			&& (token->flags & DQUOTE_STATE) == 0
			&& token->brace_buf->quoted == 0)
			pop(token, token->value[token->str_index]);
	}
}

void			lexer_set_flags(t_lexer_state *token)
{
	if (is_spec(token->value[token->str_index]))
		token->flags |= HAS_SPECIAL;
	if (token->value[token->str_index] == '"'
		&& (token->flags & QUOTE_STATE) == 0)
		token->flags ^= DQUOTE_STATE;
	if (token->value[token->str_index] == '\''
		&& (token->flags & DQUOTE_STATE) == 0)
		token->flags ^= QUOTE_STATE;
	retrieve_brace(token);
	if ((token->flags & ISOPEN_STATE) == 0 && (token->brace_buf != NULL
		|| (token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE)))
		token->flags ^= ISOPEN_STATE;
	else if (token->flags & ISOPEN_STATE && token->brace_buf == NULL
		&& !(token->flags & QUOTE_STATE) && !(token->flags & DQUOTE_STATE))
		token->flags ^= ISCLOSED_STATE;
}
