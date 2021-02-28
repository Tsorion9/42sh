/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_word.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:58:27 by jsance            #+#    #+#             */
/*   Updated: 2021/01/08 13:40:24 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "readline.h"
#include "expansions.h"

void			lexer_state_word_esc(t_lexer_state *token)
{
	char	*input;
	size_t	i;

	input = NULL;
	if (CURRENT_CHAR == '\n')
	{
		token->str_index--;
		token->tk_len--;
		input = line_42sh(get_prompt(PS2));
		if (input && !*(input))
		{
			token->tk_type = TOKEN_END;
			ft_fprintf(STDERR_FILENO, "%s\n", E_SYN_UNEXPECT_EOF);
			return ;
		}
		i = token->str_index;
		replace_value(&token->value, input, &i, 2);
		free(input);
		lexer_state_word(token);
	}
	else if (CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
}

/*
** Token delimiters
*/

int				is_shellspec(char c, t_lexer_state *token)
{
	if (c == '\n' || (ft_strchr("|><;&", c) != NULL))
		return (FUNC_SUCCESS);
	if (!(token->flags & DOLLAR_STATE) && ft_strchr("()", c) != NULL)
		return (FUNC_SUCCESS);
	if (token->brace_buf == NULL && (token->flags & DOLLAR_STATE))
		token->flags &= (token->flags ^ DOLLAR_STATE);
	return (FUNC_FAIL);
}

/*
** Jump in then '$' founded
** '$' skipped via lexer_change_state
** Checking:
**		@Parameter Expansion
**		@Command Sabstitution
**		@Arithmetic Expansion
** If nothing sabstitution or expansions founded then resume checking word
** If we in the end of line then it's something like that: "123$", but
** we can get 123$123${test$ -- need to close sentence with '}'
*/

void			identify_candidates(t_lexer_state *token)
{
	if (CURRENT_CHAR == '\0')
		token->tk_type = WORD;
	else if (CURRENT_CHAR == '{' && (token->flags & QUOTE_STATE) == 0)
	{
		push(token, '}');
		if (token->flags & DQUOTE_STATE)
			token->brace_buf->quoted = 1;
		lexer_change_state(token, &lexer_state_word);
	}
	else if (CURRENT_CHAR == '(' && (token->flags & DQUOTE_STATE) == 0)
	{
		token->flags |= DOLLAR_STATE;
		push(token, ')');
		if (token->flags & DQUOTE_STATE)
			token->brace_buf->quoted = 1;
		if (token->value[token->str_index + 1] == '(')
			lexer_change_state(token, &identify_candidates);
		else
			lexer_change_state(token, &lexer_state_word);
	}
	else
		lexer_state_word(token);
}

static void		lexer_state_quotes(t_lexer_state *token)
{
	if (CURRENT_CHAR == '$')
		lexer_change_state(token, identify_candidates);
	else
		lexer_change_state(token, lexer_state_word);
}

void			lexer_state_word(t_lexer_state *token)
{
	char *input;

	lexer_set_flags(token);
	input = NULL;
	if (CURRENT_CHAR == '\\' && (token->flags & QUOTE_STATE) == 0)
		lexer_change_state(token, &lexer_state_word_esc);
	else if (!is_shellspec(CURRENT_CHAR, token) && !ft_isblank(CURRENT_CHAR)
						&& CURRENT_CHAR != '\0' && CURRENT_CHAR != '$')
		lexer_change_state(token, &lexer_state_word);
	else if (((token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE))
			&& CURRENT_CHAR != '\0')
		lexer_state_quotes(token);
	else if ((token->flags & ISOPEN_STATE)
		&& (CURRENT_CHAR == '\0' || CURRENT_CHAR == '\n'))
		lexer_unclosed_state(token);
	else if (CURRENT_CHAR == '$' && (token->flags & QUOTE_STATE) == 0)
		lexer_change_state(token, &identify_candidates);
	else if ((token->flags & ISOPEN_STATE))
		lexer_change_state(token, &lexer_state_word);
	else
		token->tk_type = WORD;
}
