/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_new_user_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 10:17:45 by mphobos           #+#    #+#             */
/*   Updated: 2021/03/08 10:17:47 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline.h"

void	set_new_user_in(const char *str)
{
	size_t len;

	len = ft_strlen(str) / MIN_CMD_LENGTH;
	rp(NULL)->max_len = MIN_CMD_LENGTH * (len + 1);
	free(rp(NULL)->user_in);
	if (!(rp(NULL)->user_in = (char*)xmalloc(sizeof(char) * rp(NULL)->max_len)))
		reset_exit(1);
	ft_strcpy(rp(NULL)->user_in, str);
	rp(NULL)->len = ft_strlen(rp(NULL)->user_in);
	rp(NULL)->index = rp(NULL)->len;
}
