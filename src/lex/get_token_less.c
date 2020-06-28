/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_less.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:08 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:09 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_less(char *user_in, int *index)
{
	t_token	ret_token;

	ret_token.token_type = LESS;
	(*index)++;
	if (*index <= (int)ft_strlen(user_in) && user_in[*index] == '<')
	{
		ret_token.token_type = LESS_LESS;
		(*index)++;
	}
	else if (*index <= (int)ft_strlen(user_in) && user_in[*index] == '&')
	{
		ret_token.token_type = LESS_AND;
		(*index)++;
	}
	return (ret_token);
}
