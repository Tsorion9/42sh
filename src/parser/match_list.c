/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   match_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:26 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:51 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	match_list_dash(t_deque **command, t_deque **tokbuf_g)
{
	t_deque	*tokbuf_l;

	tokbuf_l = NULL;
	if (gett(tokbuf_g, &tokbuf_l)->token_type != sep)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (check_parser_signals());
	}
	if (match_pipeline(command, tokbuf_g) == PARSER_FAILURE)
	{
		ungett(tokbuf_g, &tokbuf_l);
		return (check_parser_signals());
	}
	match_list_dash(command, tokbuf_g);
	erase_tokbuf(&tokbuf_l);
	return (check_parser_signals());
}

int	match_list(t_deque **command, t_deque **tokbuf_g)
{
	if (match_pipeline(command, tokbuf_g) == PARSER_FAILURE)
		return (PARSER_FAILURE);
	return (match_list_dash(command, tokbuf_g));
}
