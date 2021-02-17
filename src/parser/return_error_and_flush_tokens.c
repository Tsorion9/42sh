/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_error_and_flush_tokens.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 21:51:28 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 21:51:29 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	return_err_and_flush_tokens(t_deque **tokbuf_g, t_deque **tokbuf_l)
{
	flush_tokbuf(tokbuf_g, tokbuf_l);
	return (PARSER_ERROR);
}
