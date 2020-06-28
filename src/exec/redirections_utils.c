/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:42 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:36:16 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "static_env.h"

#include <fcntl.h>
#include <unistd.h>
#include "fd_crutch.h"
#include "err_const.h"

int	fail_open_file_error(t_io_redir *redir)
{
	ft_fprintf(2, "Error: could not open file %s\n",\
			(char *)redir->where->content);
	if (!isatty(0))
		exit(-1);
	return (1);
}

int	no_file_error(t_io_redir *redir)
{
	ft_fprintf(2, "Error: file %s does not exist\n",\
			(char *)redir->where->content);
	if (!isatty(0))
		exit(-1);
	return (1);
}

int	normal_redirection(t_io_redir *redir)
{
	int	copy;
	int errors;

	errors = 0;
	if (!ft_strcmp((char *)redir->where->content, CLOSE_STREAM))
	{
		close(redir->fd);
		return (0);
	}
	if (write(ft_atoi(redir->where->content), &errors, 0) == -1)
	{
		ft_fprintf(2, "%s: (%s)\n", RO_REDIR_FD, redir->where->content);
		return (1);
	}
	copy = dup(ft_atoi(redir->where->content));
	if (copy == -1)
	{
		write(2, BAD_FD_ERRMSG, sizeof(BAD_FD_ERRMSG));
		close(redir->fd);
		return (1);
	}
	errors = dup2_wrapper(copy, redir->fd);
	close(copy);
	return (errors == -1 ? errors : 0);
}
