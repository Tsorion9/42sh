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

#include "21sh.h"

void		expand_user_in(void)
{
	char	*tmp;

	tmp = xmalloc(rp()->max_len);
	ft_strcpy(tmp, rp()->user_in);
	free(rp()->user_in);
	rp()->max_len *= 2;
	if (!(rp()->user_in = (char*)xmalloc(sizeof(char) * rp()->max_len)))
		reset_exit(1);
	ft_strcpy(rp()->user_in, tmp);
	free(tmp);
}
