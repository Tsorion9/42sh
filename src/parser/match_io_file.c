/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_io_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:50 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	figure_out_fd(t_io_redir *redir)
{
	if (redir->fd)
		return ;
	if (redir->operation == greater ||\
		redir->operation == dgreat ||\
		redir->operation == gr_and)
		redir->fd = 1;
}

int			match_io_file(t_io_redir *redir, t_deque **tokbubf_g)
{
	t_deque			*tokbuf_l;
	t_token_type	type;
	t_token			*tok;

	tokbuf_l = NULL;
	type = gett(tokbubf_g, &tokbuf_l)->token_type;
	if (type != less && type != greater && type != gr_and\
			&& type != lessand && type != dgreat && type != clobber)
	{
		ungett(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	redir->operation = type;
	figure_out_fd(redir);
	if ((tok = gett(tokbubf_g, &tokbuf_l))->token_type != word &&\
			tok->token_type != number)
	{
		flush_tokbuf(tokbubf_g, &tokbuf_l);
		return (PARSER_FAILURE);
	}
	ft_lstadd_data(&(redir->where), (void *)(ft_strdup(tok->attribute)), 0);
	erase_tokbuf(&tokbuf_l);
	return (check_parser_signals());
}
