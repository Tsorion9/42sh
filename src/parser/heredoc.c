#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libft.h"

int		*intnew(int x)
{
	int	*res;

	res = xmalloc(sizeof(int));
	*res = x;
	return (res);
}

void noncritical_error(char *text)
{
	ft_fprintf(2, "%s\n", text);
}

/*
** Create pipe; Write content into it;
** return int *fd; allocated in heap. 
** Free the content
*/

static int		*create_tmp_file(char *content)
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

static char 	*temporary_readline_wrapper(char *prompt)
{
	char	*s;
	int		gnl_status;

	if (isatty(0))
		return (readline(prompt));
	gnl_status = get_next_line(0, &s);
	if (gnl_status == -1)
		return (NULL);
	if (gnl_status == 0)
		return (NULL);
	return (s);
}

static char		*gather_string_literal(char *here_eof)
{
	char	*literal;
	char	*line;
	char	*tmp;
	char	*tmp1;

	literal = ft_strdup("");
	while (1)
	{
		line = temporary_readline_wrapper(get_prompt(PS2));
		if (!line)
			ft_fprintf(2, EOF_WRN_S, here_eof);
		if (!line || ft_strcmp(line, here_eof) == 0)
		{
			free(line);
			return (literal);
		}
		else
		{
			tmp1 = ft_strjoin(line, "\n");
			tmp = ft_strjoin(literal, tmp1);
			ft_memdel((void *)&literal);
			ft_memdel((void *)&line);
			ft_memdel((void *)&tmp1);
			literal = tmp;
		}
	}
}

void	*heredoc_action(t_heredoc_action action, void *data)
{
	static t_deque	*eof_words;
	static t_deque	*fd_deque;
	char			*current_strlit;
	char			*here_eof;

	if (action == is_empty)
		return ((eof_words && eof_words->first) ? NULL : (void *)1);
	if (action == add_hd)
		return (push_back(&eof_words, data));
	if (action == add_fd)
	{
		here_eof = (char *)pop_front(eof_words);
		current_strlit = gather_string_literal(here_eof);
		free(here_eof);
		push_back(&fd_deque, create_tmp_file(current_strlit));
		return (NULL);
	}
	if (action == pop_fd)
		return (pop_front(fd_deque));
	else
	{
		return (NULL);
	}
}

void	gather_heredocs(void)
{
	while (!heredoc_action(is_empty, NULL))
		heredoc_action(add_fd, NULL);
}
