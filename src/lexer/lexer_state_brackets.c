/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_brackets.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 21:00:19 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 21:00:20 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				ft_isbrackets(char c)
{
	if (c == '(' || c == ')')
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

static void		lexer_state_rbracket(t_lexer_state *token)
{
	token->tk_type = RBRACKET;
}

static void		lexer_state_lbracket(t_lexer_state *token)
{
	token->tk_type = LBRACKET;
}

void			lexer_state_brackets(t_lexer_state *token)
{
	if (token->value[token->str_index] == '(')
		lexer_change_state(token, &lexer_state_lbracket);
	else
		lexer_change_state(token, &lexer_state_rbracket);
}
