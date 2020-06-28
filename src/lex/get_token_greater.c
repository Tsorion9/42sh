/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_greater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:50 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:16:50 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_greater(char *user_in, int *index)
{
	t_token	ret_token;

	ret_token.token_type = GREATER;
	(*index)++;
	if (*index <= (int)ft_strlen(user_in) && user_in[*index] == '>')
	{
		ret_token.token_type = GREATER_GREATER;
		(*index)++;
	}
	else if (*index <= (int)ft_strlen(user_in) && user_in[*index] == '&')
	{
		ret_token.token_type = GREATER_AND;
		(*index)++;
	}
	return (ret_token);
}
