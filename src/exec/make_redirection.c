/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 15:16:10 by jsance            #+#    #+#             */
/*   Updated: 2021/03/07 15:16:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "exec.h"

static int	make_heredoc_redirection(t_redirect *redirect)
{
	int		pipefd[2];
	pid_t	child;

	pipe(pipefd);
	dup2(pipefd[0], redirect->redirector->fd);
	close_wrapper(pipefd[0]);
	child = fork();
	if (child)
	{
		close_wrapper(pipefd[1]);
		return (0);
	}
	else
	{
		close_wrapper(redirect->redirector->fd);
		ft_fprintf(pipefd[1], "%s", redirect->heredoc_value);
		exit(0);
	}
}

static int	contain_ambiguous(t_redirect *redirect)
{
	t_redirect		*tmp;
	t_redirector	*redir;

	tmp = redirect;
	while (tmp)
	{
		redir = tmp->redirector;
		if (redir->splitted_filename && redir->splitted_filename->next)
			return (FUNC_SUCCESS);
		tmp = tmp->next;
	}
	return (FUNC_FAIL);
}

static int	file_redirection(t_redirect *redirect, int flags, int mode)
{
	int				fd;

	if (contain_ambiguous(redirect))
	{
		ft_fprintf(STDERR_FILENO, "%s: %s: %s\n",
			"42sh", redirect->redirector->filename, E_AMBIGUOUS_REDIR);
		return (1);
	}
	fd = open(redirect->redirector->filename, flags, mode);
	if (fd == -1)
	{
		ft_fprintf(STDERR_FILENO, "%s %s\n",
				"Could not open file:", redirect->redirector->filename);
		return (1);
	}
	dup2(fd, redirect->redirector->fd);
	close_wrapper(fd);
	return (0);
}

static int	try_duplicate_fd(t_redirect *redirect)
{
	int status;

	status = dup2(ft_atoi(redirect->redirector->filename),
			redirect->redirector->fd);
	if (status == -1)
	{
		ft_fprintf(STDERR_FILENO, "42sh: %d: Bad file descriptor\n",
				ft_atoi(redirect->redirector->filename));
		return (-1);
	}
	if (redirect->instruction == DUPLICAT_OUTPUT)
	{
		status = write(redirect->redirector->fd, &status, 0);
	}
	else if (redirect->instruction == DUPLICAT_INPUT)
	{
		status = read(redirect->redirector->fd, &status, 0);
	}
	if (status == -1)
	{
		ft_fprintf(STDERR_FILENO, "42sh: %d: Bad file descriptor\n",
				redirect->redirector->fd);
	}
	return (status);
}

int			make_redirection(t_redirect *redirect)
{
	int status;

	status = 0;
	if (redirect->instruction == INPUT_DIRECTION)
		status = file_redirection(redirect, O_RDONLY, 0666);
	else if (redirect->instruction == OUTPUT_DIRECTION)
		status = file_redirection(redirect, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	else if (redirect->instruction == DOUBLE_OUTPUT_DIRECTION)
		status = file_redirection(redirect, O_WRONLY | O_CREAT | O_APPEND,
				0666);
	else if (redirect->instruction == DOUBLE_INPUT_DERECTION)
		status = make_heredoc_redirection(redirect);
	if (redirect->instruction == DUPLICAT_OUTPUT ||
			redirect->instruction == DUPLICAT_INPUT)
	{
		if (!ft_strcmp(redirect->redirector->filename, "-"))
		{
			return (close_wrapper(redirect->redirector->fd));
		}
		status = try_duplicate_fd(redirect);
	}
	return (status);
}
