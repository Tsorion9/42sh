/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_str.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:14:18 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/24 19:25:08 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

t_str		*init_str(void)
{
	t_str	*new_str;

	if (!(new_str = (t_str*)xmalloc(sizeof(t_str))))
		reset_exit(1);
	if (!(new_str->buf = (char*)xmalloc(sizeof(char) * MIN_CMD_LENGTH)))
		reset_exit(1);
	new_str->len = 0;
	new_str->max_len = MIN_CMD_LENGTH;
	new_str->index = 0;
	return (new_str);
}

void		expand_str(t_str *str)
{
	char	tmp[str->max_len];

	ft_strcpy(tmp, str->buf);
	free(str->buf);
	str->max_len += MIN_CMD_LENGTH;
	if (!(str->buf = (char*)xmalloc(sizeof(char) * str->max_len)))
		reset_exit(1);
	ft_strcpy(str->buf, tmp);
}

void		free_str(t_str *str)
{
	if (str)
	{
		if (str->buf)
			free(str->buf);
		free(str);
	}
}
