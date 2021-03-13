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

void			lexer_state_start(t_lexer_state *token)
{
	if (token->value[token->str_index] == '|')
		lexer_change_state(token, &lexer_state_pipe);
	else if (token->value[token->str_index] == '&')
		lexer_change_state(token, &lexer_state_bg);
	else if (token->value[token->str_index] == '>')
		lexer_change_state(token, &lexer_state_great);
	else if (token->value[token->str_index] == '<')
		lexer_change_state(token, &lexer_state_less);
	else if (token->value[token->str_index] == ';')
		lexer_change_state(token, &lexer_state_semicol);
	else if (ft_isbraces(token->value[token->str_index]))
		lexer_state_braces(token);
	else if (ft_isbrackets(token->value[token->str_index]))
		lexer_state_brackets(token);
	else if (token->value[token->str_index] == '\\')
		lexer_change_state(token, &lexer_state_word_esc);
	else if (token->value[token->str_index] == '\n')
		lexer_change_state(token, &lexer_state_newline);
	else if (ft_isdigit(token->value[token->str_index]))
		lexer_change_state(token, &lexer_state_ionum);
	else
		lexer_state_word(token);
}
