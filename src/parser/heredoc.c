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
** Statically allocated fixed size
*/

static char *rnd_nonzero_str()
{
	static char s[TMPFILE_SUFFIX_SIZE];
	int	 rnd_fd;
	int	 i;

	rnd_fd = open(SYS_RNDGEN_FILENAME, O_RDONLY);
	read(rnd_fd, s, TMPFILE_SUFFIX_SIZE - 1);
	close(rnd_fd);
	i = -1;
	while (++i < TMPFILE_SUFFIX_SIZE) /* Random bytes could be zero */
	{
		if (!s[i])
			s[i] = 1;
	}
	s[TMPFILE_SUFFIX_SIZE - 1] = 0;
	return (s);
}

/*
** Return heap-allocated string
*/

static char *tmpfile_name()
{
	char	*filename;
	char	*suffix;
	char	*current;
	char	*prefix;

	prefix = DEFAULT_TMPFILE_PREFIX;
	suffix = rnd_nonzero_str();
	filename = malloc(ft_strlen(prefix) + ft_strlen(suffix) + 1);
	current = filename;
	while ((*current++ = *prefix++))
		;
	current--;
	while ((*current++ = *suffix++))
		;
	return (filename);		
}

/*
** Return fd
** TODO: probably /tmp does not exist 
** (User should configure a place for tmpfiles)
*/

static int	open_tmpfile(char *content)
{
	char	*filename;
	int		fd;

	filename = tmpfile_name();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	ft_putstr_fd(content, fd);
	close(fd);					/* We are not allowed to use lseek() in 21sh */
	fd = open(filename, O_RDONLY, 0666);
	if (fd == -1)
	{
		ft_putstr("Somebody deleted our temporary file =) \n");
		return (-1);
	}
	free(filename);
	return (fd);
}

/*
** Create temporary file; Write content into it;
** return int *fd; allocated in heap. 
** Free the content
*/

static int		*create_tmp_file(char *content)
{
	int	*fd;

	fd = intnew(open_tmpfile(content));
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
