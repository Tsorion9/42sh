/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anton <a@b>                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:31:25 by anton             #+#    #+#             */
/*   Updated: 2020/06/28 11:40:49 by anton            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "libft.h"

int				*intnew(int x)
{
	int	*res;

	res = xmalloc(sizeof(int));
	*res = x;
	return (res);
}

void			noncritical_error(char *text)
{
	ft_fprintf(2, "%s\n", text);
}

/*
** Create pipe; Write content into it;
** return int *fd; allocated in heap.
** Free the content
*/

int				*create_tmp_file(char *content)
{
	int	fd[2];
	int	*res;

	if (-1 == pipe(fd))
	{
		ft_putstr_fd("Pipe failed\n", 2);
		exit(-1);
	}
	if (!fork())
		exit(write(fd[1], content, ft_strlen(content)));
	close(fd[1]);
	res = intnew(fd[0]);
	free(content);
	return (res);
}
