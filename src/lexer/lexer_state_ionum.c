/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_ionum.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 12:23:46 by jsance            #+#    #+#             */
/*   Updated: 2021/02/28 12:23:47 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lexer_state_ionum(t_lexer_state *token)
{
	if (ft_isdigit(token->value[token->str_index]))
		lexer_change_state(token, &lexer_state_ionum);
	else if (token->value[token->str_index] == '>'
			|| token->value[token->str_index] == '<')
		token->tk_type = IO_NUMBER;
	else
		lexer_state_word(token);
}
