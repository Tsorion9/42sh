/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_user_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:05 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:05 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

void		expand_user_in(void)
{
	char	*tmp;

	tmp = xmalloc(rp(NULL)->max_len);
	ft_strcpy(tmp, rp(NULL)->user_in);
	free(rp(NULL)->user_in);
	rp(NULL)->max_len *= 2;
	if (!(rp(NULL)->user_in = (char*)xmalloc(sizeof(char) * rp(NULL)->max_len)))
		reset_exit(1);
	ft_strcpy(rp(NULL)->user_in, tmp);
	free(tmp);
}
