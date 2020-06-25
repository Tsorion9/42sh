/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_crutch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 18:53:46 by anton             #+#    #+#             */
/*   Updated: 2020/06/25 18:56:26 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	{
		write(2, "Warning! pipe() failed.\n",\
				sizeof("Warning! pipe() failed.\n"));
	}
	fd_crutch(fd);
	return (res);
}
