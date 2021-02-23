/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_unclosed_state.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:42:26 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 21:42:27 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "readline.h"

static char		get_quote(t_lexer_state *token)
{
	if (token->flags & QUOTE_STATE)
		return ('\'');
	else if (token->flags & DQUOTE_STATE)
		return ('"');
	return (token->brace_buf->brace);
}

void			lexer_unclosed_state(t_lexer_state *token)
{
	char *input;

	input = line_42sh(get_prompt(PS2));
	if (!input)
	{
		token->tk_type = TOKEN_CTRL_C;
		return ;
	}
	if (!*(input))
	{
		token->tk_type = TOKEN_END;
		ft_fprintf(STDERR_FILENO, "%s`%c'\n",
					E_UNEXPECTED_EOF, get_quote(token));
		ft_fprintf(STDERR_FILENO, "%s\n", E_SYN_UNEXPECT_EOF);
		free(input);
		return ;
	}
	token->value = ft_strjoinfreefree(token->value, input);
	if (CURRENT_CHAR == '\n')
		lexer_change_state(token, &lexer_state_word);
	else
		lexer_state_word(token);
}
