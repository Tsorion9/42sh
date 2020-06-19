#include "heredoc.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "libft.h"

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
		exit (-1);
	}
	if (!fork())
		exit(write(fd[1], content, ft_strlen(content)));
	close(fd[1]);
	res = intnew(fd[0]);
	free(content);
	return (res);
}

/*
** TODO: refactor readline
*/

static char 	*temporary_readline_wrapper(char *prompt)
{
	char	*s;
	int		gnl_status;

	if (isatty(0))
		return (readline(prompt));
	gnl_status = get_next_line(0, &s); // TODO: Check corner cases with EOF and empty string
	if (gnl_status == -1)
		return (NULL);
	if (gnl_status == 0)
	{
		//free(s);
		return (NULL);
	}

	return (s);
}

/*
	FIX BEFORE SUBMITTING THE PROJECT

	TODO:
	If any part of word is quoted, the delimiter shall be formed by performing 
	quote removal on word, and the here-document lines shall not be expanded. 
	Otherwise, the delimiter shall be the word itself.

	If no part of word is quoted, all lines of the here-document shall be 
	expanded for parameter expansion, command substitution, and arithmetic 
	expansion. In this case, the <backslash> in the input behaves as the 
	<backslash> inside double-quotes (see Double-Quotes). However, the 
	double-quote character ( ' )' shall not be treated specially within a 
	here-document, except when the double-quote appears within 
	"$()", "``", or "${}".

	TODO: multiline here-doc delimiter 

	(Bash does not support both of them)
*/

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
			ft_fprintf(2, "21sh: Warning! Here document delimited by end-of-file instead of %s\n", here_eof);
		if (!line || ft_strcmp(line, here_eof) == 0)
		{
			free(line);
			return (literal);
		}
		else
		{
			tmp1 = ft_strjoin(line, "\n");
			tmp = ft_strjoin(literal, tmp1); // TODO: o(n^2), fix later maybe
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
		current_strlit = gather_string_literal((here_eof = (char *)pop_front(eof_words)));
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
