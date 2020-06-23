/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:17:16 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:17:16 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	get_token_pipe(int *index)
{
	t_token	ret_token;

	ret_token.token_type = PIPE;
	(*index)++;
	return (ret_token);
}
