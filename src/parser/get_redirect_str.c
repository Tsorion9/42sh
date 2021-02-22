/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirect_str.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 22:28:32 by jsance            #+#    #+#             */
/*   Updated: 2021/02/15 22:28:33 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static char	*join_redirects_parts(int fd, char *file, const char *instruct)
{
	char		*str_fd;
	char		*res;
	size_t		len;

	str_fd = ft_itoa(fd);
	len = ft_strlen(str_fd) + ft_strlen(instruct) + ft_strlen(file) + 1;
	res = ft_strnew(len);
	ft_strcpy(res, str_fd);
	ft_strcat(res, instruct);
	ft_strcat(res, " ");
	ft_strcat(res, file);
	free(str_fd);
	return (res);
}

char		*redirects_str(t_redirect *redirects)
{
	const char	*instruction;
	char		*str_redir;
	char		*filename;
	int			fd;
	t_redirect	*tmp;

	if (redirects == NULL)
		return (NULL);
	tmp = redirects;
	str_redir = ft_strnew(0);
	while (tmp)
	{
		fd = tmp->redirector->fd;
		filename = tmp->redirector->filename;
		instruction = get_instruction(tmp->instruction);
		str_redir = ft_strjoinfreefree(
				str_redir,
				join_redirects_parts(fd, filename, instruction));
		if (tmp->next)
			str_redir = ft_strjoinfreefree(str_redir, ft_strdup(" "));
		tmp = tmp->next;
	}
	return (str_redir);
}
