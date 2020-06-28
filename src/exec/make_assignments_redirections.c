/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_assignments_redirections.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:39 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:53 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "static_env.h"

#include <fcntl.h>
#include <unistd.h>
#include "redirections_utils.h"
#include "fd_crutch.h"

/*
** as_wrd is string in format name=value
** free the as_wrd (Or better not?)
*/

static void	make_assignment(t_env env, char *as_wrd)
{
	char	*name;
	char	*value;

	split_env_entry(as_wrd, &name, &value);
	ft_setenv(env, name, value);
	free(name);
}

static int	get_oflags(t_token_type op)
{
	if (op == less)
		return (O_RDONLY);
	if (op == greater)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	if (op == dgreat)
		return (O_WRONLY | O_APPEND | O_CREAT);
	return (0);
}

static int	redirect_next_heredoc(int fd)
{
	int	*heredoc;

	heredoc = heredoc_action(pop_fd, NULL);
	if (!heredoc)
		return (-1);
	if (dup2_wrapper(*heredoc, fd) == -1)
		return (-1);
	close(*heredoc);
	free(heredoc);
	return (0);
}

/*
** TODO: fd should be open for reading or writing respectively
** (DONE): try to write 0 bytes into the file and check the return value
**
** TODO(2): redir->where is a list actually. Process error "ambigous redirect"
*/

static int	make_io_redir(t_io_redir *redir)
{
	int	fd;

	if (redir->operation == lessand || redir->operation == gr_and)
		return (normal_redirection(redir));
	if (redir->operation == dless || redir->operation == dlessash)
		return (redirect_next_heredoc(redir->fd));
	if (redir->operation == less &&\
			access((char *)redir->where->content, F_OK) == -1)
		return (no_file_error(redir));
	fd = open((char *)redir->where->content,\
			get_oflags(redir->operation), 0666);
	if (fd == -1)
		return (fail_open_file_error(redir));
	dup2_wrapper(fd, redir->fd);
	close(fd);
	return (0);
}

/*
** TODO: handle possible errors
*/

int			make_assignments_redirections(t_simple_cmd *cmd)
{
	t_ar		*ar;
	char		*as_wrd;
	t_env		env;
	int			any_errors;

	env = static_env_action(get, NULL);
	while ((ar = (t_ar *)pop_front(cmd->arl)))
	{
		if (ar->what == assignment)
		{
			as_wrd = (char *)ar->data;
			make_assignment(env, as_wrd);
		}
		else
		{
			any_errors = make_io_redir((t_io_redir *)ar->data);
			if (any_errors)
			{
				rm_ar(ar);
				return (1);
			}
		}
		rm_ar(ar);
	}
	return (0);
}
