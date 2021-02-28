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
