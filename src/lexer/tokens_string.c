/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:41:47 by nriker            #+#    #+#             */
/*   Updated: 2020/10/06 22:00:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*single_tk_str(t_tokens type)
{
	if (type == AND_IF)
		return ("&&");
	else if (type == OR_IF)
		return ("||");
	else if (type == DLESS)
		return ("<<");
	else if (type == DGREAT)
		return (">>");
	else if (type == LESS)
		return ("<");
	else if (type == GREAT)
		return (">");
	else if (type == LESSAND)
		return ("<&");
	else if (type == GREATAND)
		return (">&");
	else if (type == PIPE)
		return ("|");
	else if (type == SEMICOL)
		return (";");
	else if (type == BG)
		return ("&");
	return ("UNKNOWN TOKEN");
}

char		*get_token_str(t_tokens type)
{
	if (type == START)
		return ("START");
	else if (type == WORD)
		return ("WORD");
	else if (type == IO_NUMBER)
		return ("IO_NUM");
	else if (type == NEWLINE)
		return ("\\n");
	else if (type == TOKEN_END)
		return ("end of file");
	else if (type == RBRACKET)
		return (")");
	else if (type == LBRACKET)
		return ("(");
	else if (type == LBRACE)
		return ("{");
	else if (type == RBRACE)
		return ("}");
	else if (type == SIGNAL || type == TOKEN_CTRL_C)
		return ("SIGNAL");
	else
		return (single_tk_str(type));
}
