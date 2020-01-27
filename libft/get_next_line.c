/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 21:42:24 by mphobos           #+#    #+#             */
/*   Updated: 2019/09/25 15:33:56 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_flist	*del_file(t_flist *files, t_flist *file)
{
	t_flist	*ptr;

	ptr = files;
	if (files == file)
	{
		if (files->next != NULL)
			files = files->next;
		free(files->content);
		free(files);
		files = NULL;
		file = NULL;
	}
	else
	{
		while (ptr->next != file && ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = file->next;
		free(file->content);
		free(file);
	}
	return (files);
}

static t_flist	*add_search_file(const int fd, t_flist *files)
{
	if (files == NULL)
	{
		files = (t_flist*)malloc(sizeof(t_flist));
		files->fd = fd;
		files->content = NULL;
		files->next = NULL;
	}
	else
	{
		while (files->next != NULL && files->fd != fd)
			files = files->next;
		if (files->fd != fd)
		{
			files->next = (t_flist*)malloc(sizeof(t_flist));
			files = files->next;
			files->fd = fd;
			files->content = NULL;
			files->next = NULL;
		}
	}
	return (files);
}

static int		get_new_line(t_flist *file, char **line)
{
	char	*tmp;
	size_t	len;

	len = 0;
	while (file->content[len] != '\n' && file->content[len] != '\0')
		len++;
	*line = ft_strsub(file->content, 0, len);
	if (file->content[len] == '\n')
		tmp = ft_strdup(file->content + len + 1);
	else
		tmp = ft_strdup(file->content + len);
	free(file->content);
	file->content = tmp;
	return (1);
}

int				gnl_sup(int fd, char *buf, t_flist *file)
{
	int		ret;
	char	*tmp;

	while ((ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (file->content == NULL)
			file->content = ft_strnew(1);
		tmp = ft_strjoin(file->content, buf);
		free(file->content);
		file->content = tmp;
		if (ft_strchr(file->content, '\n'))
			break ;
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static t_flist	*files;
	t_flist			*file;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (files == NULL)
		files = add_search_file(fd, files);
	file = add_search_file(fd, files);
	if (fd == -1 || file == NULL || read(fd, buf, 0) == -1)
		return (-1);
	ret = gnl_sup(fd, buf, file);
	if (ret == 0 && (file->content == NULL || file->content[0] == '\0'))
	{
		files = del_file(files, file);
		return (0);
	}
	return (get_new_line(file, line));
}
