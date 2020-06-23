/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_attrinute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:16:42 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:16:42 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

char		*create_attribute(t_str *attr)
{
	char	*attribute;

	attr->buf[attr->index] = 0;
	if (!(attribute = ft_strdup(attr->buf)))
		reset_exit(0);
	return (attribute);
}
