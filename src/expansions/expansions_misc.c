/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_misc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 20:00:35 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 20:00:37 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

int	is_valid_var_char(char c)
{
	if (ft_isalpha(c) || c == '_')
		return (VALID_VAR_CHAR);
	return (INVALID_VAR_CHAR);
}

int	is_valid_var_name(char *s)
{
	int i;

	i = -1;
	while (s[++i])
	{
		if (i == 0 && ft_isdigit(s[i]))
			return (0);
		if (!is_valid_var_char(s[i]) && !ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

int	expasnion_status(int status)
{
	static int	g_status;

	if (status == GET_STATUS)
		return (g_status);
	g_status = status;
	return (g_status);
}
