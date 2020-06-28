/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_ar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:23 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:48 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"

/*
** Add assignment or redirection to command
*/

void	add_ar(t_simple_cmd **cmd, void *data, t_ear what)
{
	t_ar	*new;

	new = xmalloc(sizeof(t_ar));
	new->what = what;
	new->data = (what == assignment) ? ((t_token *)data)->attribute : data;
	push_back(&((*cmd)->arl), (void *)new);
	if (what == assignment)
		free(data);
}
