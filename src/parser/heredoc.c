#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


/*
** Allocate the number in heap
*/

int		*intnew(int x)
{
	int	*res;

	res = malloc(sizeof(int));
	*res = x;
	return (res);
}

void noncritical_error(char *text)
{
	ft_fprintf(2, "%s\n", text);
}

/*
** Create temporary file; Write content into it;
** return int *fd; allocated in heap. 
** Free the content
*/

static int		*create_tmp_file(char *content)
{
	int	*fd;

	fd = intnew(open(TMP_DIR,  __O_TMPFILE | O_RDWR));
	if (*fd == -1)
		noncritical_error(TMPF_ERRMESSG);
	else
		ft_putstr_fd(content, *fd);
	free(content);
	return (fd);
}

static char		*gather_string_literal(char *here_eof)
{
	char	*literal;
	char	*line;
	char	*tmp;

	literal = ft_strdup("");
	while (1)
	{
		line = readline(HEREDOC_PROMPT);
		if (ft_strcmp(line, here_eof) == 0)
			return (literal);
		else
		{
			tmp = ft_strjoin(literal, line); // o(n^2), fix later maybe
			ft_memdel((void *)&literal);
			ft_memdel((void *)&line);
			literal = tmp;
		}
	}
}

void	*heredoc_action(t_heredoc_action action, void *data)
{
	static t_deque	*eof_words;
	static t_deque	*fd_deque;
	char			*current_strlit;	

	if (action == is_empty)
		return (eof_words && eof_words->first ? (void *)1 : NULL);
	if (action == add_hd)
		return (push_back(&eof_words, data));
	if (action == add_fd)
	{
		current_strlit = gather_string_literal((char *)pop_front(eof_words));
		push_back(&fd_deque, create_tmp_file(current_strlit));
		return (NULL);
	}
	if (action == pop_fd)
		return (pop_front(fd_deque));
	else
	{
		return (NULL);
		//deque_del(&eof_words);
		//deque_del(&fd_deque);
	}
}

void	gather_heredocs(void)
{
	while (heredoc_action(is_empty, NULL))
		heredoc_action(add_fd, NULL);
}
