/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:43:59 by anton             #+#    #+#             */
/*   Updated: 2020/06/26 23:28:19 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

# include "deque.h"
# include "inc21sh.h"
# include "libft.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define EOF_WRN_S "Warning! Heredoc delimited by end-of-file instead of %s\n"

/*
** Some comment
*/

typedef enum	e_heredoc_action
{
	cleanup,
	add_hd,
	add_fd,
	pop_fd,
	is_empty,
	total_cleanup
}				t_heredoc_action;

void			*heredoc_action(t_heredoc_action action, void *data);
void			gather_heredocs(void);

#endif
