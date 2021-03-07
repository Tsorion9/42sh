/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_heredoc_routines.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:19:45 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 15:19:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "libft.h"

void		clean_all_heredoc(t_heredoc **heredoc)
{
	t_heredoc *tmp;

	tmp = *heredoc;
	while (tmp)
	{
		ft_strdel(tmp->value);
		free(tmp->delimiter);
		tmp = tmp->next;
		free(*heredoc);
		*heredoc = tmp;
	}
}

void		delete_heredoc(t_heredoc **heredoc)
{
	if ((*heredoc)->delimiter)
		ft_strdel(&(*heredoc)->delimiter);
	free(*heredoc);
	*heredoc = NULL;
}
