/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:50:09 by jsance            #+#    #+#             */
/*   Updated: 2020/10/13 21:45:37 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include <stdio.h>

void			lexer_set_flags(t_lexer_state *token)
{
	if (is_spec(CURRENT_CHAR))
		token->flags |= HAS_SPECIAL;
	if (CURRENT_CHAR == '"' && (token->flags & QUOTE_STATE) == 0)
		token->flags ^= DQUOTE_STATE;
	if (CURRENT_CHAR == '\'' && (token->flags & DQUOTE_STATE) == 0)
		token->flags ^= QUOTE_STATE;
	if ((CURRENT_CHAR == '}' || CURRENT_CHAR == ')')
	&& (token->flags & QUOTE_STATE) == 0 && (token->flags & DQUOTE_STATE) == 0)
		pop(token, CURRENT_CHAR);
	if ((token->flags & ISOPEN_STATE) == 0 && (token->head != NULL
		|| (token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE)))
		token->flags ^= ISOPEN_STATE;
	else if (token->flags & ISOPEN_STATE && token->head == NULL
		&& !(token->flags & QUOTE_STATE) && !(token->flags & DQUOTE_STATE))
		token->flags ^= ISCLOSED_STATE;
}

void			lexer_change_state(t_lexer_state *token,
									void (*lexer_state)(t_lexer_state *))
{
	(token->str_index)++;
	(token->tk_len)++;
	lexer_state(token);
}

void			lexer_state_semicol(t_lexer_state *token)
{
	token->tk_type = SEMICOL;
}

void			lexer_state_newline(t_lexer_state *token)
{
	token->tk_type = NEWLINE;
}

void 			lexer_state_rbracket(t_lexer_state *token)
{
	token->tk_type = RBRACKET;
}

void 			lexer_state_lbracket(t_lexer_state *token)
{
	token->tk_type = LBRACKET;
}

void 			lexer_state_brackets(t_lexer_state *token)
{
	if (CURRENT_CHAR == '(')
		lexer_change_state(token, &lexer_state_lbracket);
	else
		lexer_change_state(token, &lexer_state_rbracket);
}

int 			ft_isbrackets(char c)
{
	if (c == '(' || c == ')')
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

int 			ft_isbraces(char c)
{
    if (c == '{' || c == '}')
        return (FUNC_SUCCESS);
    return (FUNC_FAIL);
}

void 			lexer_state_rbrace(t_lexer_state *token)
{
    token->tk_type = RBRACE;
}

void 			lexer_state_lbrace(t_lexer_state *token)
{
    token->tk_type = LBRACE;
}

int             ft_isdelimeterblank(char c)
{
    if (c <= 32 || c > 126)
        return (FUNC_SUCCESS);
    return (FUNC_FAIL);
}

void            lexer_state_braces(t_lexer_state *token)
{
    if (!ft_isdelimeterblank(token->value[token->str_index + 1]))
        lexer_state_word(token);
    else if (CURRENT_CHAR == '{')
        lexer_change_state(token, &lexer_state_lbrace);
    else
        lexer_change_state(token, &lexer_state_rbrace);
}

void			lexer_state_start(t_lexer_state *token)
{
	if (CURRENT_CHAR == '|')
		lexer_change_state(token, &lexer_state_pipe);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_bg);
	else if (CURRENT_CHAR == '>')
		lexer_change_state(token, &lexer_state_great);
	else if (CURRENT_CHAR == '<')
		lexer_change_state(token, &lexer_state_less);
	else if (CURRENT_CHAR == ';')
		lexer_change_state(token, &lexer_state_semicol);
    else if (ft_isbraces(CURRENT_CHAR))
        lexer_state_braces(token);
	else if (ft_isbrackets(CURRENT_CHAR))
		lexer_state_brackets(token);
	else if (CURRENT_CHAR == '\\')
		lexer_change_state(token, &lexer_state_word_esc);
	else if (CURRENT_CHAR == '\n')
		lexer_change_state(token, &lexer_state_newline);
	else if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(token, &lexer_state_ionum);
	else
		lexer_state_word(token);
}
