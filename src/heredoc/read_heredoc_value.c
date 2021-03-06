/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_heredoc_value.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 15:26:27 by jsance            #+#    #+#             */
/*   Updated: 2021/03/06 15:26:28 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "heredoc.h"
#include "readline.h"
#include "environment.h"

static void	update_value(char **value, char **line)
{
	if (*value == NULL)
		*value = *line;
	else
		*value = ft_strjoinfreefree(*value, *line);
}

static char	*handle_sigint(int *heredoc_sigint, char **value)
{
	*heredoc_sigint = 1;
	free(*value);
	return (NULL);
}

/*
** return NULL if SIGINT arrived
*/

char		*read_heredoc_value(char *delimiter, int *heredoc_sigin)
{
	char	*value;
	char	*line;

	value = NULL;
	while (1)
	{
		line = line_42sh(ft_getenv(env, "PS2"));
		if (line == NULL)
			return (handle_sigint(heredoc_sigin, &value));
		if (!*line && !isatty(STDIN_FILENO))
			ft_fprintf(STDERR_FILENO, "%s\n", HEREDOC_WARNING);
		if (ft_strequ(line, delimiter) || !*line)
		{
			ft_strdel(&line);
			line = ft_strnew(0);
			update_value(&value, &line);
			break ;
		}
		update_value(&value, &line);
	}
	return (value);
}
