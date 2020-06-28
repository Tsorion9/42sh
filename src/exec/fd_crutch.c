/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_crutch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:53:46 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:34:52 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "err_const.h"

int		*fd_crutch(int fd[2])
{
	static int	fd_save[2];

	if (fd)
	{
		fd_save[0] = fd[0];
		fd_save[1] = fd[1];
		return (fd_save);
	}
	return (fd_save);
}

int		pipe_wrapper(int fd[2])
{
	int	res;

	res = pipe(fd);
	if (res == -1)
		write(2, PIPE_FAIL_ERRMSG, sizeof(PIPE_FAIL_ERRMSG));
	fd_crutch(fd);
	return (res);
}

int		dup2_wrapper(int old_fd, int new_fd)
{
	int	res;

	res = dup2(old_fd, new_fd);
	return (res);
}
