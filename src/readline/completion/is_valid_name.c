/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexbuyanov <alexbuyanov@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:31:00 by jbrinksm          #+#    #+#             */
/*   Updated: 2020/12/12 15:28:39 by alexbuyanov      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

int		is_valid_name_char(char c)
{
	return (ft_isalnum(c) == true || ft_strchr("*-_~!@#$%^.,[]+?", c) != NULL);
}

int		is_valid_name(char *str)
{
	int i;

	if (str == NULL || *str == '\0' || *str == '=')
		return (false);
	i = 0;
	while (str[i] != '\0' && str[i] != '=')
	{
		if (is_valid_name_char(str[i]) == false)
			return (false);
		i++;
	}
	return (true);
}
