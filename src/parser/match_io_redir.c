/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_io_redir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:26 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static void	enter(t_deque **tokbuf_l, t_io_redir **redir)
{
	*tokbuf_l = NULL;
	*redir = xmalloc(sizeof(t_io_redir));
	if (*redir)
	{
		(*redir)->fd = 0;
		(*redir)->operation = 0;
		(*redir)->where = NULL;
	}
}

int			match_io_redirect(t_simple_cmd *cmd, t_deque **tokbubf_g)
{
	t_deque		*tokbuf_l;
	t_io_redir	*redir;

	enter(&tokbuf_l, &redir);
	if (gett(tokbubf_g, &tokbuf_l)->token_type != number)
		ungett(tokbubf_g, &tokbuf_l);
	else
		redir->fd = ft_atoi(((t_token *)deque_n_th(tokbuf_l, 0))->attribute);
	if (match_io_file(redir, tokbubf_g) == PARSER_SUCCESS ||\
		match_io_here(redir, tokbubf_g) == PARSER_SUCCESS)
	{
		erase_tokbuf(&tokbuf_l);
		add_ar(&cmd, redir, redirection);
		return (check_parser_signals());
	}
	rm_redir(redir);
	flush_tokbuf(tokbubf_g, &tokbuf_l);
	return (PARSER_FAILURE);
}
