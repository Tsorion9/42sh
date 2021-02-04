#include <unistd.h>
#include <stdio.h>
#include "lexer.h"
#include "parser.h"
#include "exec.h"

/*
** Content size is neeeded only for libft compatability
*/

static void	del_simple(void *content, size_t content_size)
{
	free(content);
}

static char				*concat_and_free(t_list **l, unsigned int total_len)
{
	char	*c;
	size_t	i;

	i = 0;
	c = 0;
	if (total_len + 1)
		c = (char *)malloc(total_len + 1);
	while (*l)
	{
		ft_memcpy(c + i, (const void *)(*l)->content, (*l)->content_size);
		i += (*l)->content_size;
		ft_lstdelone(l, &del_simple);
	}
	c[i] = 0;
	return (c);
}

static char *read_from_pipe(int fd)
{
	static char buf[1002];
	t_list *l;
	size_t bytes_read;
	size_t total_len;

	bytes_read = 0;
	total_len = 0;
	l = NULL;
	while ((bytes_read = read(fd, buf, 1000)) > 0)
	{
		//buf[bytes_read + 1] = 0;
		//printf("Read buf: %s\n Bytes %d \n", buf, bytes_read);
		total_len += bytes_read;
		l = ft_lstappend(l, buf, bytes_read);
	}
	return (concat_and_free(&l, total_len));
}

void command_substitution(char **s)
{
	t_complete_cmd *cmd;
	char *tmp;
	pid_t child;
	int	pipefd[2];

	tmp = ft_strdup(*s);
	cmd = parser(&tmp);

	pipe(pipefd);
	child = fork();
	if (child) /* Parent */
	{
		close(pipefd[1]);
		*s = read_from_pipe(pipefd[0]);
		//printf("Substituted: %s\n", *s);
		close(pipefd[0]);
	}
	else /* Child */
	{
		//sleep(1);
		close(pipefd[0]);
		//close(STDIN_FILENO);
		dup2(pipefd[1], STDERR_FILENO);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		interactive_shell = 0;
		exec_complete_cmd(cmd);
		exit(0);
	}

}
