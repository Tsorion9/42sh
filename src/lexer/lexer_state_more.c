/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_more.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:03:46 by jsance            #+#    #+#             */
/*   Updated: 2020/10/08 20:35:45 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lexer_state_and_if(t_lexer_state *token)
{
	token->tk_type = AND_IF;
}

void			lexer_state_bg(t_lexer_state *token)
{
	if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_and_if);
	else
		token->tk_type = BG;
}

void			lexer_state_orif(t_lexer_state *token)
{
	token->tk_type = OR_IF;
}

void			lexer_state_pipe(t_lexer_state *token)
{
	if (CURRENT_CHAR == '|')
		lexer_change_state(token, &lexer_state_orif);
	else
		token->tk_type = PIPE;
}
