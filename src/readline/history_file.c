/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 18:13:28 by mphobos           #+#    #+#             */
/*   Updated: 2020/06/23 18:13:31 by mphobos          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc21sh.h"
#include "environment.h"
#include "static_env.h"

static int	open_21sh_history(int mode)
{
	int		fd;
	char	*home_dir;
	char	*file_path;

	if (!(home_dir = ft_getenv(static_env_action(get, NULL), "HOME")))
		return (-1);
	if (!(file_path = ft_strjoin(home_dir, "/.21sh_history")))
		return (-1);
	fd = open(file_path, mode, __S_IREAD | __S_IWRITE);
	free(file_path);
	return (fd);
}

void		load_on_file_history(t_history *history)
{
	int		fd;
	char	c;
	t_str	*str;

	if ((fd = open_21sh_history(O_RDONLY)) < 0)
		return ;
	str = init_str();
	while (read(fd, &c, 1) > 0)
	{
		if (str->index >= str->max_len)
			expand_str(str);
		if (c == '\n')
		{
			str->buf[str->index] = '\0';
			add_to_start_history(history, str->buf, ft_strlen(str->buf));
			str->index = 0;
		}
		else
		{
			str->buf[str->index] = c;
			str->index++;
		}
	}
	free_str(str);
	close(fd);
}

static void	save_in_file_history_sup(int fd, int n, char *history)
{
	int		i;
	char	buf[MIN_CMD_LENGTH];

	i = 0;
	while (n != HISTSIZE)
	{
		if (history[i] == '\n')
			n--;
		i++;
	}
	ft_strcpy(buf, history + i);
	write(fd, buf, ft_strlen(buf));
	write(fd, "\n", 1);
}

int			str_naa(char *user_in)
{
	int n;

	n = 0;
	while (*user_in != 0)
	{
		if (*user_in == '\n')
			n++;
		user_in++;
	}
	return (n);
}

/*
** Сохраняет историю в файл, начиная с указателя history.
*/

void		save_in_file_history(t_history *history)
{
	int	fd;
	int	n;

	if ((fd = open_21sh_history(O_WRONLY | O_TRUNC | O_CREAT)) < 0)
		return ;
	n = 0;
	while (history->next && n < HISTSIZE)
	{
		history = history->next;
		n += str_naa(history->str) + 1;
	}
	if (n > HISTSIZE)
	{
		save_in_file_history_sup(fd, n, history->str);
		if (history->prev)
			history = history->prev;
	}
	while (history->prev)
	{
		write(fd, history->str, history->len);
		write(fd, "\n", 1);
		history = history->prev;
	}
	close(fd);
}
