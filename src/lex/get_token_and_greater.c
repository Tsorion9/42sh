/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_and_greater.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:43 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:16:44 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_and_greater(char **user_in, int *index, t_str *attr)
{
	t_token	ret_token;

	if ((*user_in)[*index + 1] == '>')
	{
		ret_token.token_type = AND_GREATOR;
		(*index) += 2;
	}
	else
	{
		write_char_to_buf(*user_in, index, attr);
		ret_token = get_token_word(user_in, index, attr);
	}
	return (ret_token);
}
