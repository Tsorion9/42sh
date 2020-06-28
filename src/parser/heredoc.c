/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:24 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 13:25:14 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"
#include "heredoc_utils.h"
#include "memdel3.h"
#include "fuck_norme_lexer_state.h"
#include "gather_string_literal.h"

void			close_free(void *data)
{
	close(*(int *)data);
	free(data);
}

void			*heredoc_total_cleanup(t_deque **eof_words, t_deque **fd_deque)
{
	deque_del(eof_words, free);
	deque_del(fd_deque, close_free);
	return (NULL);
}

void			*heredoc_add_fd(t_deque **eof_words, t_deque **fd_deque)
{
	char			*current_strlit;
	char			*here_eof;

	here_eof = (char *)pop_front(*eof_words);
	current_strlit = gather_string_literal(here_eof);
	if (fuck_checklist_signal_state(0, 0))
	{
		heredoc_action(total_cleanup, NULL);
		free(here_eof);
		return (NULL);
	}
	free(here_eof);
	push_back(fd_deque, create_tmp_file(current_strlit));
	return (NULL);
}

void			*heredoc_action(t_heredoc_action action, void *data)
{
	static t_deque	*eof_words;
	static t_deque	*fd_deque;

	if (action == is_empty)
		return ((eof_words && eof_words->first) ? NULL : (void *)1);
	if (action == add_hd)
		return (push_back(&eof_words, data));
	if (action == add_fd)
		return (heredoc_add_fd(&eof_words, &fd_deque));
	if (action == pop_fd)
		return (pop_front(fd_deque));
	if (action == total_cleanup)
		return (heredoc_total_cleanup(&eof_words, &fd_deque));
	return (NULL);
}

void			gather_heredocs(void)
{
	while (!heredoc_action(is_empty, NULL))
		heredoc_action(add_fd, NULL);
}
