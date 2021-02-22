/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:53:10 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/25 15:34:06 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <errno.h>

# define MAX_OPEN_FILES 1024

# ifndef BUFF_SIZE
#  define BUFF_SIZE 1000
# endif

/*
** Max depth of binary tree, can be from 1 to 64
*/

# ifndef DEPTH
#  define DEPTH 14
# endif

typedef struct	s_unread_buff
{
	char		*data;
	int			pos;
	int			nbytes;
	int			eof;
	int			io_err;
	int			nl_found;
}				t_unread_buff;

int				get_next_line(const int fd, char **line);

#endif
