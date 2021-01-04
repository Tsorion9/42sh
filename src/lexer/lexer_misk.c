/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_misk.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:11:08 by jsance            #+#    #+#             */
/*   Updated: 2020/10/06 21:04:03 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NewLexer.h"

int				is_spec(char c)
{
	if (c != '\0' && ft_strchr("-~$?/\\'\"", c) != NULL)
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

int				ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}
