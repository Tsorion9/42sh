/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_io_here.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	match_io_here(t_io_redir *redir, t_deque **tokbubf_g)
{
	t_deque			*tokbuf_l;
	t_token_type	type;
	t_token			*tok;

	tokbuf_l = NULL;
	type = gett(tokbubf_g, &tokbuf_l)->token_type;
	if (type != dless && type != dlessash)
	{
		ungett(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	redir->operation = type;
	if ((tok = gett(tokbubf_g, &tokbuf_l))->token_type != word)
	{
		flush_tokbuf(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	ft_lstadd_data(&redir->where, (void *)ft_strdup(tok->attribute), 0);
	heredoc_action(add_hd, (void *)ft_strdup(tok->attribute));
	erase_tokbuf(&tokbuf_l);
	return (check_parser_signals());
}
