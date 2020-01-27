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
# include <fcntl.h>

# define BUFF_SIZE 8

typedef struct		s_flist
{
	int				fd;
	char			*content;
	struct s_flist	*next;
}					t_flist;

int					get_next_line(const int fd, char **line);
#endif
