/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_line_separator.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:10 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:11 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_toket_line_separator(int *index)
{
	t_token	ret_token;

	ret_token.token_type = LINE_SEPARATOR;
	(*index)++;
	return (ret_token);
}
