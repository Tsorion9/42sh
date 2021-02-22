/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgian <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 20:20:24 by bgian             #+#    #+#             */
/*   Updated: 2019/10/11 18:37:49 by bgian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <errno.h>

static t_unread_buff	*new_buf(void)
{
	t_unread_buff	*buffer;

	buffer = (t_unread_buff *)malloc(sizeof(t_unread_buff));
	if (!buffer)
		return (0);
	buffer->data = (char *)malloc(BUFF_SIZE);
	if (!buffer->data)
	{
		free(buffer);
		return (0);
	}
	buffer->pos = 0;
	buffer->nbytes = 0;
	buffer->eof = 0;
	buffer->io_err = 0;
	buffer->nl_found = 0;
	return (buffer);
}

static char				*concat_and_free(t_list **l, unsigned int total_len)
{
	char	*c;
	size_t	i;

	i = 0;
	c = 0;
	if (total_len + 1)
		c = (char *)malloc(total_len + 1);
	if (!c)
	{
		errno = EOVERFLOW;
		ft_lstdel(l, &del_simple);
		return (0);
	}
	while (*l)
	{
		ft_memcpy(c + i, (const void *)(*l)->content, (*l)->content_size);
		i += (*l)->content_size;
		ft_lstdelone(l, &del_simple);
	}
	c[i] = 0;
	return (c);
}

/*
**		Append contents of buffer from pos to '\n' into list *l
**		Return number of bytes (len) extracted from buffer. Skip newline.
**		Update the current position of buffer to (len + 1) bytes
**		Update nl_found field if found '\n'
**
**		position can become > bytes_in_buff
*/

static size_t			try_buffer(t_unread_buff *buff, t_list **l)
{
	int	len;

	len = 0;
	buff->nl_found = 0;
	while (buff->pos + len < buff->nbytes)
	{
		if (buff->data[buff->pos + len] == '\n')
		{
			buff->nl_found = 1;
			break ;
		}
		len++;
	}
	*l = ft_lstappend(*l, ft_memdup(buff->data + buff->pos, len), len);
	buff->pos += len + 1;
	return ((size_t)len);
}

/*
**		First of all, try to read from buffer.
**		If nothing interesting left in buffer, read from file.
**		If nothing interesting left in file, stop and update EOF-bit
*/

static int				seek_nl(t_unread_buff *buff, int fd, t_list **l)
{
	size_t	total_len;
	size_t	prev;

	total_len = 0;
	while (1)
	{
		prev = total_len;
		errno = (total_len += try_buffer(buff, l)) < prev ? EOVERFLOW : errno;
		if (!buff->nl_found)
		{
			buff->nbytes = read(fd, buff->data, BUFF_SIZE);
			buff->pos = 0;
			if (buff->nbytes == -1)
				return (0);
			if (buff->nbytes == 0)
			{
				if (total_len == 0)
					buff->eof = 1;
				return (total_len);
			}
			continue;
		}
		return (total_len);
	}
}

/*
**		Caller should not store anything useful in *line.
**		EOF handling detatils:
**		When we return 0, *line is set to NULL
**		If EOF reached and there is still any data in buffer, reading is
**		not considered as finished, 0 is not returned.
**		If any data is appended to file after EOF, we can read it.
**
**		Other details:
**		1)*line IS freed and set to NULL in case of ANY errors
**		Absence of double free is guaranteed by function concat_and_free
**		2)l is ALWAYS freed in concat_and_free.
**		Absence of double free is guaranteed by function ft_lstdel
*/

int						get_next_line(const int fd, char **line)
{
	static t_bbtree_node	*tree;
	t_unread_buff			**buff;
	unsigned int			len;
	t_list					*l;

	errno = 0;
	l = NULL;
	if (!*(buff = (t_unread_buff **)add_index(&tree, fd, DEPTH)))
		*buff = new_buf();
	if (!*buff || !line)
		return (-1);
	(*buff)->eof = 0;
	len = (unsigned int)seek_nl(*buff, fd, &l);
	*line = concat_and_free(&l, len);
	if (errno || (*buff)->eof == 1)
	{
		free(*line);
		*line = 0;
		return (errno ? -1 : 0);
	}
	return (1);
}
