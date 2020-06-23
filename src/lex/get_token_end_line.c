/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_end_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:46 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:16:47 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_end_line(int *index)
{
	t_token	ret_token;

	*index = 0;
	ret_token.token_type = END_LINE;
	return (ret_token);
}
