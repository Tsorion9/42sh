/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:17:25 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 15:17:26 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "environment.h"
#include "expansions.h"

/*
** address_value is field address *heredoc_value of s_redirect structure
** delimiter is heredoc delimiter
*/

t_heredoc	*create_heredoc(char *delimiter, char **address_value)
{
	t_heredoc			*fresh;

	fresh = (t_heredoc*)ft_memalloc(sizeof(t_heredoc));
	if (contain_quote(delimiter))
		quote_removal(&delimiter);
	fresh->delimiter = ft_strjoin(delimiter, "\n");
	fresh->value = address_value;
	return (fresh);
}

void		add_heredoc_node(t_heredoc **heredocs, char *delimiter,
							char **address_val)
{
	t_heredoc			*tmp;

	if (*heredocs == NULL)
	{
		*heredocs = create_heredoc(delimiter, address_val);
		return ;
	}
	tmp = *heredocs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = create_heredoc(delimiter, address_val);
}

void		fill_heredoc_values(t_heredoc **heredocs_head, int *heredoc_sigint)
{
	t_heredoc		*tmp;

	tmp = *heredocs_head;
	while (tmp)
	{
		*(tmp->value) = read_heredoc_value(tmp->delimiter, heredoc_sigint);
		if (*(tmp->value) == NULL)
			return ;
		tmp = tmp->next;
		delete_heredoc(heredocs_head);
		*heredocs_head = tmp;
	}
}

/*
** address_value is field address *heredoc_value of s_redirect structure
** char *del is heredoc delimiter
** action used to identify action
*/

void		heredoc_action(int action, char *del, char **address_value,
							int *heredoc_sigint)
{
	static t_heredoc	*heredocs;

	if (action == ADD_DELIMITER)
		add_heredoc_node(&heredocs, del, address_value);
	else if (action == ADD_VALUE)
		fill_heredoc_values(&heredocs, heredoc_sigint);
	if (heredoc_sigint != NULL && *heredoc_sigint)
		clean_all_heredoc(&heredocs);
}
