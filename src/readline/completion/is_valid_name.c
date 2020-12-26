/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:31:00 by jbrinksm          #+#    #+#             */
/*   Updated: 2020/12/26 13:54:00 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int		is_valid_name_char(char c)
{
	return (ft_isalnum(c) == TRUE || ft_strchr("*-_~!@#$%^.,[]+?", c) != NULL);
}

int		is_valid_name(char *str)
{
	int i;

	if (str == NULL || *str == '\0' || *str == '=')
		return (FALSE);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (is_valid_name_char(str[i]) == FALSE)
			return (FALSE);
		i++;
	}
	return (TRUE);
}
