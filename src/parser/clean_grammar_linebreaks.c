/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_grammar_linebreaks.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:04:47 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:04:48 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_grammar_linebreaks(t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;

	tokbuf_l = NULL;
	while (gett(g_parser_input_str, tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
		erase_tokbuf(&tokbuf_l);
	ungett(tokbuf_g, &tokbuf_l);
}
