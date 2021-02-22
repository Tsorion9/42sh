/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_redirects.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 22:35:09 by jsance            #+#    #+#             */
/*   Updated: 2021/02/17 22:35:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clean_redirector(t_redirector **redirector)
{
	if ((*redirector)->filename)
		ft_strdel(&(*redirector)->filename);
	clean_words(&((*redirector)->splitted_filename));
	free(*redirector);
	*redirector = NULL;
}

void	clean_redirects(t_redirect **redirects)
{
	t_redirect *delete;

	while (*redirects != NULL)
	{
		clean_redirector(&(*redirects)->redirector);
		if ((*redirects)->heredoc_value)
			ft_strdel(&(*redirects)->heredoc_value);
		delete = *redirects;
		*redirects = (*redirects)->next;
		free(delete);
		delete = NULL;
	}
}
