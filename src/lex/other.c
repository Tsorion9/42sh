/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:48 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:49 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

bool		is_letter(char c)
{
	bool	f;

	f = true;
	if (c == '>' || c == '<' || c == '|' ||\
	c == ' ' || c == '\t' || c == ';' ||\
	c == '\'' || c == 0 || c == '&' ||\
	c == '\"' || is_ws(c))
		f = false;
	return (f);
}

bool		is_digit(char c)
{
	bool	f;

	f = false;
	if (c >= '0' && c <= '9')
		f = true;
	return (f);
}

bool		is_ws(char c)
{
	bool	f;

	f = false;
	if (c == ' ' || c == '\t')
		f = true;
	return (f);
}
