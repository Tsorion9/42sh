#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>

int		main(void)
{
	char	*arg[] = {"/bin/ls", NULL};
	char	*arg1[] = {"/bin/cat", "-e", NULL};

	int		conn[2];
	int i = 0;
	int pid;
	pipe(conn);
	if ((pid = fork()) == 0)
	{
		dup2(conn[1], 1);
		close(conn[0]);
		int		fd[2];
		pipe(fd);
		if ((pid = fork()) == 0)
		{
			dup2(fd[1], 1);
			close(fd[0]);
			execv("/bin/ls", arg);
		}
		else
		{
			close(fd[1]);
			waitpid(pid, NULL, WNOHANG);
			dup2(fd[0], 0);
			execv("/bin/cat", arg1);
		}
	}
	else
	{
		close(conn[1]);
		waitpid(pid, NULL, WNOHANG);
		dup2(conn[0], 0);
		execv("/bin/cat", arg1);
	}
	return (0);
}
