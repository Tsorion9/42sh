/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_braces.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:58:03 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 20:58:04 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				ft_isbraces(char c)
{
	if (c == '{' || c == '}')
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

static void		lexer_state_rbrace(t_lexer_state *token)
{
	token->tk_type = RBRACE;
}

static void		lexer_state_lbrace(t_lexer_state *token)
{
	token->tk_type = LBRACE;
}

static int		ft_isdelimeterblank(char c)
{
	if (c <= 32 || c > 126)
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

void			lexer_state_braces(t_lexer_state *token)
{
	if (!ft_isdelimeterblank(token->value[token->str_index + 1]))
		lexer_state_word(token);
	else if (token->value[token->str_index] == '{')
		lexer_change_state(token, &lexer_state_lbrace);
	else
		lexer_change_state(token, &lexer_state_rbrace);
}
