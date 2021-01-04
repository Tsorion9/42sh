/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_less.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:57:50 by jsance            #+#    #+#             */
/*   Updated: 2020/10/06 21:36:59 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lexer_state_dless(t_lexer_state *token)
{
	token->tk_type = DLESS;
}

void			lexer_state_lessand(t_lexer_state *token)
{
	token->tk_type = LESSAND;
}

void			lexer_state_less(t_lexer_state *token)
{
	if (CURRENT_CHAR == '<')
		lexer_change_state(token, &lexer_state_dless);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_lessand);
	else
		token->tk_type = LESS;
}
