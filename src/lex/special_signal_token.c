/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_signal_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/28 13:54:12 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 13:54:14 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

t_token	*special_signal_token(void)
{
	t_token	res;

	res.token_type = signal_token;
	res.attribute = NULL;
	return (copy_init_token(res));
}

t_token	stack_special_signal_token(void)
{
	t_token	res;

	res.token_type = signal_token;
	res.attribute = NULL;
	return (res);
}
