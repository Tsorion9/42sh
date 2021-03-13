/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fc_e.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 02:16:42 by jsance            #+#    #+#             */
/*   Updated: 2021/03/14 02:16:43 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "environment.h"
#include "builtin_fc.h"
#include "exec.h"

static void		fill_file(int first, t_fc_options *options, int fd,
							t_history *history)
{
	while (first <= options->last)
	{
		ft_fprintf(fd, "%s\n", history->str);
		if (first > options->last)
			first--;
		else
			first++;
		history = history->next;
	}
}

static void		init_start_data(t_fc_options *options, t_history **history,
												int *first)
{
	if (!(options->first))
		options->first = FC_OPERAND_FIRST_DEFAULT_VALUE;
	if (!(options->last))
		options->last = options->number_of_history;
	convert_operands_to_pisitive_history_number(options);
	*history = get_history(options, options->first);
	*first = options->first;
}

static int		create_file(void)
{
	char		filename[20];
	char		*pid;
	int			fd;

	pid = ft_itoa(getpid());
	ft_strcpy(filename, "/tmp/42sh_fc_");
	ft_strcat(filename, pid);
	ft_strdel(&pid);
	fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
		return (-1);
	return (fd);
}

static int		exec_file_str(int fd)
{
	char		*line;
	char		*total;
	int			status;

	line = NULL;
	total = ft_strnew(1);
	while (get_next_line_wrapper(fd, &line) > 0)
	{
		total = ft_strjoinfreefree(total, line);
		line = NULL;
	}
	free(line);
	status = exec_string(total);
	free(total);
	close(fd);
	return (status);
}

int				exec_fc_e(t_fc_options *options)
{
	char		filename[20];
	int			fd;
	int			first;
	t_history	*history;
	char		*editor;

	fd = create_file();
	if (fd == -1)
		return (-1);
	init_start_data(options, &history, &first);
	fill_file(first, options, fd, history);
	editor = ft_strjoin(options->editor, " ");
	editor = ft_strjoinfreefree(editor, ft_strdup(filename));
	exec_string(editor);
	free(editor);
	lseek(fd, 0, SEEK_SET);
	return (exec_file_str(fd));
}
