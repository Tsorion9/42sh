/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 12:03:43 by jsance            #+#    #+#             */
/*   Updated: 2021/01/08 13:39:30 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "readline.h"

t_lexer_state g_token;

void			free_lexer_state(t_lexer_state *token)
{
	if (token->value)
		free(token->value);
	if (token->brace_buf != NULL)
		free_quequ_lexer(&token->brace_buf);
	token->value = NULL;
	token->brace_buf = NULL;
	token->tk_len = 0;
	token->str_index = 0;
	token->flags = 0;
}

static t_token	*return_token_and_clean_state(t_lexer_state *token,
											t_tokens tk_type)
{
	t_token *fresh;

	free_lexer_state(token);
	fresh = ft_memalloc(sizeof(t_token));
	fresh->value = NULL;
	fresh->tk_type = tk_type;
	return (fresh);
}

t_token			*lexer_scanner(t_lexer_state *token)
{
	t_token		*fresh;

	token->tk_type = ERROR;
	if (token->value == NULL)
	{
		token->value = line_42sh(get_prompt(PS1));
		if (isatty(STDIN_FILENO))
			history_lexer(&token->value);
		if (token->value == NULL)
			return (return_token_and_clean_state(token, TOKEN_CTRL_C));
		if (token->value && !*(token->value))
			return (return_token_and_clean_state(token, TOKEN_END));
	}
	while (ft_isblank(token->value[token->str_index]))
		(token->str_index)++;
	lexer_state_start(token);
	fresh = get_token_to_parser(token);
	return (fresh);
}

/*
** value если value != NULL, значит не планируется использовать readline
** в лексере, потому что строка для лексического анализа уже задана.
** Ожидается полностью валидная с точки зрения lexer-a строка, это значит
** lexer не будет вызывать readline
** Передается адрес value, чтобы отслеживать когда строка кончится, то есть
** дойдет до символа конца строки, это необходимо, чтобы не вызывался readline
*/

t_token			*lexer(char **value)
{
	t_token	*token;

	if (value != NULL)
		g_token.value = *value;
	token = lexer_scanner(&g_token);
	if (value != NULL)
		*value = g_token.value;
	return (token);
}
