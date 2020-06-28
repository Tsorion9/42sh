/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_number.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:13 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:14 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_number(char **user_in, int *index, t_str *attr, \
	int prev_token)
{
	t_token	ret_token;

	while (*index <= (int)ft_strlen(*user_in) && is_digit((*user_in)[*index]))
		write_char_to_buf(*user_in, index, attr);
	if ((*user_in)[*index] == '>' || (*user_in)[*index] == '<')
	{
		ret_token.token_type = NUMBER;
		ret_token.attribute = create_attribute(attr);
	}
	else if (is_letter((*user_in)[*index]) || (*user_in)[*index] == '\'' ||\
	(*user_in)[*index] == '\"')
		ret_token = get_token_word(user_in, index, attr);
	else if (prev_token == LESS_AND || prev_token == GREATER_AND)
	{
		ret_token.token_type = NUMBER;
		ret_token.attribute = create_attribute(attr);
	}
	else
		ret_token = get_token_word(user_in, index, attr);
	return (ret_token);
}
