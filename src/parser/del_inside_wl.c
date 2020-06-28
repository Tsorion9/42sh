/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_inside_wl.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:23 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:48 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "parser.h"
#include "deque.h"
#include "libft.h"

void	rm_word(void *word)
{
	free(word);
}

void	del_inside_wl(void *content, size_t content_size)
{
	(void)content_size;
	free(content);
}
