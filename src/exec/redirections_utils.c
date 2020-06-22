/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 01:48:42 by anton             #+#    #+#             */
/*   Updated: 2020/06/23 01:48:43 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "21sh.h"
#include "static_env.h"

#include <fcntl.h>
#include <unistd.h>

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

	if (!ft_strcmp((char *)redir->where->content, CLOSE_STREAM))
	{
		close(redir->fd);
		return (0);
	}
	copy = dup(ft_atoi(redir->where->content));
	if (copy == -1)
	{
		close(redir->fd);
		return (0);
	}
	dup2(copy, redir->fd);
	close(copy);
	return (0);
}
