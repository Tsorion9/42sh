/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 19:43:27 by jsance            #+#    #+#             */
/*   Updated: 2021/01/04 21:40:15 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "parser.h"

t_complete_cmd *parser()
{
	t_complete_cmd  *complete_cmd = NULL;
    static t_deque	*tokbuf_g;
    t_deque			*tokbuf_l = NULL;

	while (gett(&tokbuf_g, &tokbuf_l)->tk_type == NEWLINE)
		erase_tokbuf(&tokbuf_l);
	ungett(&tokbuf_g, &tokbuf_l);
	if (gett(&tokbuf_g, &tokbuf_l)->tk_type == TOKEN_END)
		reset_exit(0);
	ungett(&tokbuf_g, &tokbuf_l);
    if (match_complete_command(&complete_cmd, &tokbuf_g) != PARSER_SUCCES)
    {
        ft_putstr("PARSER ERROR\n");
    }
    return (complete_cmd);
}
