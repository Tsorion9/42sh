/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_and_or.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:28:33 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:28:34 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_andor_list	*init_and_or(void)
{
	t_andor_list	*fresh;

	fresh = (t_andor_list*)ft_memalloc(sizeof(t_andor_list));
	if (!fresh)
		return (NULL);
	return (fresh);
}

void			set_type_if(t_andor_list **and_or, t_token *token)
{
	if (token->tk_type == AND_IF)
		(*and_or)->type_andor = ANDOR_AND;
	else if (token->tk_type == OR_IF)
		(*and_or)->type_andor = ANDOR_OR;
	else
		(*and_or)->type_andor = ANDOR_NONE;
}

int				match_and_or(t_andor_list **and_or, t_deque **tokbuf_g)
{
	t_deque			*tokbuf_l;

	tokbuf_l = NULL;
	*and_or = init_and_or();
	if (match_pipeline(&(*and_or)->pipeline, tokbuf_g) != PARSER_SUCCES)
		return (PARSER_ERROR);
	set_type_if(and_or, gett(g_parser_input_str, tokbuf_g, &tokbuf_l));
	if ((*and_or)->type_andor != ANDOR_NONE)
	{
		clean_grammar_linebreaks(tokbuf_g);
		if (match_and_or(&(*and_or)->next, tokbuf_g) != PARSER_SUCCES)
			return (return_err_and_flush_tokens(tokbuf_g, &tokbuf_l));
		erase_tokbuf(&tokbuf_l);
	}
	else
		ungett(tokbuf_g, &tokbuf_l);
	return (PARSER_SUCCES);
}
