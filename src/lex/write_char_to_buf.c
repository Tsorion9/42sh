/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char_to_buf.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:18:02 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:18:02 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"

void		write_char_to_buf(char *user_in, int *index, t_str *attr)
{
	if (attr->max_len <= attr->len + 1)
		expand_str(attr);
	attr->buf[attr->index] = user_in[*index];
	(*index)++;
	attr->index++;
	attr->len++;
	attr->buf[attr->index] = '\0';
}
