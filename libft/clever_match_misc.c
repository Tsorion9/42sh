/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clever_match_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 01:07:49 by jsance            #+#    #+#             */
/*   Updated: 2021/03/12 01:07:50 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		init_local_variables(char symbols[256], int *negate_result)
{
	ft_memset(symbols, 0, 256);
	*negate_result = 0;
}

void		increment_2(char **pattern, char **not_quoted)
{
	(*pattern)++;
	(*not_quoted)++;
}
