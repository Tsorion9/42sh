/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_cmd_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:56:30 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:56:31 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_word_list	*create_word_node(char *word)
{
	t_word_list	*fresh;

	fresh = (t_word_list*)ft_memalloc(sizeof(t_word_list));
	if (!fresh)
		return (NULL);
	fresh->word = ft_strdup(word);
	fresh->need_quote_rm = 1;
	return (fresh);
}

/*
** cmd_prefix [WORD [cmd_suffix]?]? | WORD [cmd_suffix]?
** Если префикса нет, то WORD является обязательной лексемой
** Иначе WORD является опциональным
*/

int			match_cmd_word(t_simple_cmd **simple_cmd, t_deque **tokbuf_g)
{
	t_deque		*tokbuf_l;
	t_token		*token;
	t_redirect	*redirects;

	redirects = (*simple_cmd)->redirects;
	tokbuf_l = NULL;
	token = gett(g_parser_input_str, tokbuf_g, &tokbuf_l);
	if (token->tk_type == WORD)
	{
		add_word_to_list(&(*simple_cmd)->words, create_word_node(token->value));
		erase_tokbuf(&tokbuf_l);
		return (PARSER_SUCCES);
	}
	ungett(tokbuf_g, &tokbuf_l);
	return ((redirects != NULL) ? PARSER_SUCCES : PARSER_ERROR);
}
